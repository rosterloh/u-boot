/*
 * (C) Copyright 2013
 * Cogent Healthcare Systems, <www.cogenthcs.com>
 *
 * Author :
 *	Richard Osterloh <richard.osterloh@gmail.com>
 *
 * Derived from Beagle Board and 3430 SDP code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <netdev.h>
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/mem.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/omap_gpmc.h>
#include <asm/gpio.h>
#include <i2c.h>
#include <asm/mach-types.h>
#include <linux/mtd/nand.h>
#include "castorII.h"
#include <asm/arch/sys_proto.h>
#include <asm/omap_musb.h>
#include <asm/errno.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/musb.h>
#include <command.h>
#ifdef CONFIG_USB_EHCI
#include <usb.h>
#include <asm/ehci-omap.h>
#endif

#include <asm/omap_gpio.h>
#include <asm/arch/dss.h>
#include <asm/arch/clock.h>

DECLARE_GLOBAL_DATA_PTR;

#define TWL4030_I2C_BUS					0
#define EXPANSION_EEPROM_I2C_BUS		1
#define EXPANSION_EEPROM_I2C_ADDRESS	0x53

#define CASTORII_GPIO_ETH_RST 173

#if defined(CONFIG_CMD_NET)
static void setup_net_chip(void);
static void reset_net_chip(void);
#endif

/* GPMC definitions for LAN9221 chip */
static const u32 gpmc_lan_config[] = {
    NET_LAN9221_GPMC_CONFIG1,
    NET_LAN9221_GPMC_CONFIG2,
    NET_LAN9221_GPMC_CONFIG3,
    NET_LAN9221_GPMC_CONFIG4,
    NET_LAN9221_GPMC_CONFIG5,
    NET_LAN9221_GPMC_CONFIG6,
    /*CONFIG7- computed as params */
};

/*
 * Routine: board_init
 * Description: Early hardware init.
 */
int board_init(void)
{
	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_CASTORII;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

#ifdef CONFIG_SPL_BUILD
/*
 * Routine: get_board_mem_timings
 * Description: If we use SPL then there is no x-loader nor config header
 * so we have to setup the DDR timings ourself on the first bank.  This
 * provides the timing values back to the function that configures
 * the memory.
 */
void get_board_mem_timings(struct board_sdrc_timings *timings)
{
	int pop_mfr, pop_id;

	/*
	 * We need to identify what PoP memory is on the board so that
	 * we know what timings to use.  To map the ID values please see
	 * nand_ids.c
	 */
	identify_nand_chip(&pop_mfr, &pop_id);

	if (pop_mfr == NAND_MFR_HYNIX && pop_id == 0xbc) {
		/* 256MB DDR */
		timings->mcfg = HYNIX_V_MCFG_200(256 << 20);
		timings->ctrla = HYNIX_V_ACTIMA_200;
		timings->ctrlb = HYNIX_V_ACTIMB_200;
	} else {
		/* 128MB DDR */
		timings->mcfg = MICRON_V_MCFG_165(128 << 20);
		timings->ctrla = MICRON_V_ACTIMA_165;
		timings->ctrlb = MICRON_V_ACTIMB_165;
	}
	timings->rfr_ctrl = SDP_3430_SDRC_RFR_CTRL_165MHz;
	timings->mr = MICRON_V_MR_165;
}
#endif

/*
 * Routine: castorII_power_init
 * Description: Configure the outputs of the TPS65950
 * LDOs. This should be done as early as possible. Taken 
 * from twl4030_power_init routine
 */
void castorII_power_init(void)
{
	/* set VAUX3 to 1.8V */
	twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VAUX3_DEDICATED,
				TWL4030_PM_RECEIVER_VAUX3_VSEL_18,
				TWL4030_PM_RECEIVER_VAUX3_DEV_GRP,
				TWL4030_PM_RECEIVER_DEV_GRP_P1);

	/* set VAUX2 to 1.8V */
	twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VAUX2_DEDICATED,
				TWL4030_PM_RECEIVER_VAUX2_VSEL_18,
				TWL4030_PM_RECEIVER_VAUX2_DEV_GRP,
				TWL4030_PM_RECEIVER_DEV_GRP_P1);

	/* set VPLL2 to 1.8V */
	twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VPLL2_DEDICATED,
				TWL4030_PM_RECEIVER_VPLL2_VSEL_18,
				TWL4030_PM_RECEIVER_VPLL2_DEV_GRP,
				TWL4030_PM_RECEIVER_DEV_GRP_ALL);
}
/*
static struct musb_hdrc_config musb_config = {
	.multipoint     = 1,
	.dyn_fifo       = 1,
	.num_eps        = 16,
	.ram_bits       = 12,
};

static struct omap_musb_board_data musb_board_data = {
	.interface_type	= MUSB_INTERFACE_ULPI,
};

static struct musb_hdrc_platform_data musb_plat = {
#if defined(CONFIG_MUSB_HOST)
	.mode           = MUSB_HOST,
#elif defined(CONFIG_MUSB_GADGET)
	.mode		= MUSB_PERIPHERAL,
#else
#error "Please define either CONFIG_MUSB_HOST or CONFIG_MUSB_GADGET"
#endif
	.config         = &musb_config,
	.power          = 100,
	.platform_ops	= &omap2430_ops,
	.board_data		= &musb_board_data,
};
*/
/*
 * Routine: misc_init_r
 * Description: Init ethernet (done here so udelay works)
 */
int misc_init_r(void)
{
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);

	castorII_power_init();
	
	setup_net_chip();

	reset_net_chip();

	dieid_num_r();

	//musb_register(&musb_plat, &musb_board_data, (void *)MUSB_BASE);

	return 0;
}

/*
 * Routine: set_muxconf_regs
 * Description: Setting up the configuration Mux registers specific to the
 *		hardware. Many pins need to be moved from protect to primary
 *		mode.
 */
void set_muxconf_regs(void)
{
	MUX_CASTORII();
}

/*
 * Routine: setup_net_chip
 * Description: Setting up the configuration GPMC registers specific to the
 *		Ethernet hardware.
 */
static void setup_net_chip(void)
{
	struct ctrl *ctrl_base = (struct ctrl *)OMAP34XX_CTRL_BASE;

	/* lan9221 chip */
	enable_gpmc_cs_config(gpmc_lan_config, &gpmc_cfg->cs[2], 0x2C000000,
			GPMC_SIZE_16M);

	/* Enable off mode for NWE in PADCONF_GPMC_NWE register */
	writew(readw(&ctrl_base ->gpmc_nwe) | 0x0E00, &ctrl_base->gpmc_nwe);
	/* Enable off mode for NOE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_noe) | 0x0E00, &ctrl_base->gpmc_noe);
	/* Enable off mode for ALE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_nadv_ale) | 0x0E00,
		&ctrl_base->gpmc_nadv_ale);
}

/**
 * Reset the ethernet chip.
 */
static void reset_net_chip(void)
{
	int ret;
	int rst_gpio;

	rst_gpio = CASTORII_GPIO_ETH_RST;

	ret = gpio_request(rst_gpio, "");
	if (ret < 0) {
		printf("Unable to get GPIO %d\n", rst_gpio);
		return ;
	}

	/* Configure as output */
	gpio_direction_output(rst_gpio, 0);

	/* Send a pulse on the GPIO pin */
	gpio_set_value(rst_gpio, 1);
	udelay(1);
	gpio_set_value(rst_gpio, 0);
	udelay(1);
	gpio_set_value(rst_gpio, 1);
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;

	struct eth_device *dev;
	uchar eth_addr[6];

	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);

	if (!eth_getenv_enetaddr("ethaddr", eth_addr)) {
		dev = eth_get_dev_by_index(0);
		if (dev) {
			eth_setenv_enetaddr("ethaddr", dev->enetaddr);
		} else {
			printf("castorII: Couldn't get eth device\n");
			rc = -1;
		}
	}

	#if defined(CONFIG_USB_ETHER) && defined(CONFIG_MUSB_GADGET)
	rc = usb_eth_initialize(bis);
	#endif

	return rc;
}

#if defined(CONFIG_VIDEO) && !defined(CONFIG_SPL_BUILD)
/* Address of the framebuffer in RAM. */
#define FB_START_ADDRESS 0x88000000

static struct panel_config lcd_cfg = {
	{
		.lcd_size		= PANEL_LCD_SIZE(800, 480),
		.timing_h       = DSS_HBP(46) | DSS_HFP(180) | DSS_HSW(30),
		.timing_v       = DSS_VBP(10) | DSS_VFP(22) | DSS_VSW(13),
		.pol_freq       = 0x00004000, /* Pol Freq */
		.divisor        = 0x0001000E, /* 36Mhz Pixel Clock */
		.panel_type     = ACTIVE_DISPLAY, /* TFT */
		.data_lines     = LCD_INTERFACE_24_BIT,
		.load_mode      = 0x02, /* Frame Mode */
		.panel_color	= 0,
		.gfx_format		= GFXFORMAT_RGB24_UNPACKED,
	}
};

int board_video_init(void)
{
	struct prcm *prcm_base = (struct prcm *)PRCM_BASE;
	
	void *fb;

	fb = (void *)FB_START_ADDRESS;

	lcd_cfg.frame_buffer = fb;
	
	setbits_le32(&prcm_base->fclken_dss, FCK_DSS_ON);
	setbits_le32(&prcm_base->iclken_dss, ICK_DSS_ON);

	omap3_dss_panel_config(&lcd_cfg);
	omap3_dss_enable();

	return 0;
}
#endif

#if defined(CONFIG_USB_EHCI) && !defined(CONFIG_SPL_BUILD)
/* Call usb_stop() before starting the kernel */
void show_boot_progress(int val)
{
	if (val == BOOTSTAGE_ID_RUN_OS)
		usb_stop();
}

static struct omap_usbhs_board_data usbhs_bdata = {
	.port_mode[0] = OMAP_EHCI_PORT_MODE_PHY,
	.port_mode[1] = OMAP_USBHS_PORT_MODE_UNUSED,
	.port_mode[2] = OMAP_EHCI_PORT_MODE_PHY
};

int ehci_hcd_init(int index, struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
	return omap_ehci_hcd_init(&usbhs_bdata, hccr, hcor);
}

int ehci_hcd_stop(int index)
{
	return omap_ehci_hcd_stop();
}

#endif /* CONFIG_USB_EHCI */
