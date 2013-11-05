/*
 * Configuration settings for the Cogent Healthcare Systems Castor II board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CASTORII_H
#define __CASTORII_H

#include <asm/sizes.h>

/* High Level Configuration Options */
#define CONFIG_OMAP					/* in a TI OMAP core */
#define CONFIG_OMAP34XX				/* which is a 34XX */
#define CONFIG_CASTORII				/* working with Castor II */
#define CONFIG_OMAP_GPIO
#define CONFIG_OMAP_COMMON

#define CONFIG_SDRC					/* The chip has SDRC controller */

#include <asm/arch/cpu.h>			/* get chip and board defs */
#include <asm/arch/omap3.h>
#include <asm/mach-types.h>

/* Display CPU and Board information */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

/* Clock Defines */
#define V_OSCK			26000000	/* Clock output from T2 */
#define V_SCLK			(V_OSCK >> 1)

#define CONFIG_MISC_INIT_R			/* call misc_init_r() to make sure to remap flashes correctly */

#define CONFIG_CMDLINE_TAG			/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_OF_LIBFDT			/* Device Tree */
#define CONFIG_CMD_BOOTZ
#define CONFIG_SUPPORT_RAW_INITRD

/* Hardware drivers */

/* NS16550 Configuration */
#define V_NS16550_CLK				48000000	/* 48MHz (APLL96/2) */

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK

/* select serial console configuration */
#define CONFIG_CONS_INDEX			3
#define CONFIG_SYS_NS16550_COM3		OMAP34XX_UART3
#define CONFIG_SERIAL3				3

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE				115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_OMAP_HSMMC
/* Partition tables */
#define CONFIG_EFI_PARTITION
#define CONFIG_DOS_PARTITION
/* USB
 *
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDC for Device functionalities.
 */
/*#define CONFIG_MUSB_HCD*/
#define CONFIG_MUSB_UDC
#define CONFIG_USB_OMAP3
#define CONFIG_TWL4030_USB

#ifdef CONFIG_USB_OMAP3

#ifdef CONFIG_MUSB_HCD
#define CONFIG_CMD_USB

#define CONFIG_USB_STORAGE
#define CONGIG_CMD_STORAGE
#define CONFIG_CMD_FAT

#ifdef CONFIG_USB_KEYBOARD
#define CONFIG_SYS_USB_EVENT_POLL
#define CONFIG_PREBOOT			"usb start"
#endif /* CONFIG_USB_KEYBOARD */

#endif /* CONFIG_MUSB_HCD */

#ifdef CONFIG_MUSB_UDC
/* USB device configuration */
#define CONFIG_USB_DEVICE
#define CONFIG_USB_TTY
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

/* Change these to suit your needs */
#define CONFIG_USBD_VENDORID		0x0451
#define CONFIG_USBD_PRODUCTID		0x5678
#define CONFIG_USBD_MANUFACTURER	"Cogent Healthcare Systems"
#define CONFIG_USBD_PRODUCT_NAME	"CastorII"
#endif /* CONFIG_MUSB_UDC */

#endif /* CONFIG_USB_OMAP3 */

/* Status LED */
#define CONFIG_STATUS_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define STATUS_LED_BIT			0x01
#define STATUS_LED_STATE		STATUS_LED_ON
#define STATUS_LED_PERIOD		(CONFIG_SYS_HZ / 2)
#define STATUS_LED_BIT1			0x02
#define STATUS_LED_STATE1		STATUS_LED_ON
#define STATUS_LED_PERIOD1		(CONFIG_SYS_HZ / 2)
#define STATUS_LED_BOOT			STATUS_LED_BIT1
#define STATUS_LED_GREEN		STATUS_LED_BIT

/* commands to include */
#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_EXT2			/* EXT2 Support				*/
#define CONFIG_CMD_EXT4			/* EXT4 Support				*/
#define CONFIG_CMD_FAT			/* FAT support				*/
/*#define CONFIG_CMD_JFFS2*/	/* JFFS2 Support			*/
#define CONFIG_CMD_FS_GENERIC
/*#define CONFIG_FIT*/			/* enable FIT image support     */
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE			/* needed for UBI */	
#define CONFIG_LZO
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS		/* Enable MTD parts commands	*/
#define CONFIG_MTD_DEVICE		/* needed for mtdparts commands */
/*#define MTDIDS_DEFAULT			"nand0=nand"*/
 #define MTDIDS_DEFAULT			"nand0=omap2-nand.0"
#define MTDPARTS_DEFAULT		"mtdparts=nand:512k(x-loader),"\
								"1920k(u-boot),128k(u-boot-env),"\
								"5m(kernel),-(fs)"

#define CONFIG_CMD_I2C			/* I2C serial bus support	*/
#define CONFIG_CMD_MMC			/* MMC support				*/
#define CONFIG_USB_STORAGE		/* USB storage support		*/
#ifdef CONFIG_BOOT_ONENAND
#define CONFIG_CMD_ONENAND		/* ONENAND support			*/
#endif
#ifdef CONFIG_BOOT_NAND
#define CONFIG_CMD_NAND			/* NAND support				*/
#endif
#define CONFIG_CMD_LED			/* LED support				*/
#define CONFIG_CMD_SETEXPR		/* Evaluate expressions		*/
#define CONFIG_CMD_GPIO     	/* Enable gpio command 		*/

#undef CONFIG_CMD_FLASH			/* flinfo, erase, protect	*/
#undef CONFIG_CMD_FPGA			/* FPGA configuration Support	*/
#undef CONFIG_CMD_IMI			/* iminfo					*/
#undef CONFIG_CMD_IMLS			/* List all found images	*/

#define CONFIG_CMD_NET			/* bootp, tftpboot, rarpboot*/
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_NFS			/* NFS support				*/
/*#define CONFIG_CMD_EEPROM*/

#define CONFIG_SYS_NO_FLASH
#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED	100000
#define CONFIG_SYS_I2C_SLAVE	1
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_DRIVER_OMAP34XX_I2C
#define CONFIG_VIDEO_OMAP3		/* DSS Support			*/

/* TWL4030 */
#define CONFIG_TWL4030_POWER
/*#define CONFIG_TWL4030_LED*/

#define CONFIG_HOSTNAME castorII

/* Environment information */
#define CONFIG_BOOTDELAY		3

#define CONFIG_EXTRA_ENV_SETTINGS \
	"usbtty=cdc_acm\0" \
	"loadaddr=0x82000000\0" \
	"kernel_addr=82000000\0" \
	"uboot_addr=0x80000\0" \
	"rdaddr=0x81000000\0" \
	"fdt_high=0xffffffff\0" \
	"fdtaddr=0x80f80000\0" \
	"dtb_addr=0x81600000\0" \
	"hostname=" __stringify(CONFIG_HOSTNAME) "\0" \
	"bootfile=" __stringify(CONFIG_HOSTNAME) "/zImage\0" \
	"u-boot=" __stringify(CONFIG_HOSTNAME) "/u-boot.img\0" \
	"mlo=" __stringify(CONFIG_HOSTNAME) "/MLO\0" \
	"dtb=" __stringify(CONFIG_HOSTNAME) "/"	__stringify(CONFIG_HOSTNAME) ".dtb\0" \
	"ubifs=" __stringify(CONFIG_HOSTNAME) "/ubifs.img\0" \
	"kernel_fs=/boot/zImage\0" \
	"dtb_fs=/boot/" __stringify(CONFIG_HOSTNAME) ".dtb\0" \
	"console=ttyO2,115200n8\0" \
	"mpurate=auto\0" \
	"optargs=\0" \
	"vram=12M\0" \
	"dvimode=1024x768MR-16@60\0" \
	"defaultdisplay=dvi\0" \
	"mmcdev=0\0" \
	"nandroot=ubi0:rootfs ubi.mtd=4\0" \
	"nandrootfstype=ubifs\0" \
	"nandargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"mpurate=${mpurate} " \
		"vram=${vram} " \
		"omapfb.mode=dvi:${dvimode} " \
		"omapfb.debug=y " \
		"omapdss.def_disp=${defaultdisplay} " \
		"root=${nandroot} " \
		"rootfstype=${nandrootfstype}\0" \
	"netdev=eth0\0" \
	"rootpath=/opt/rootfs\0"	\
	"nfsargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"mpurate=${mpurate} " \
		"vram=${vram} " \
		"omapfb.mode=dvi:${dvimode} " \
		"omapfb.debug=y " \
		"omapdss.def_disp=${defaultdisplay} " \
		"root=/dev/nfs rw " \
		"nfsroot=${serverip}:${rootpath}\0" \
	"nandboot=echo Booting from nand ...; " \
		"run nandargs; " \
		"nand read ${loadaddr} 280000 500000; " \
		"bootz ${loadaddr}\0" \
	"load_ubifs=tftp ${loadaddr} ${ubifs}\0" \
	"update_ubifs=ubi part ${part};ubi write ${loadaddr} ${vol} ${filesize}\0" \
	"upd_ubifs=run load_ubifs update_ubifs\0" \
	"init_ubi=nand erase.part ubi;ubi part ${part};" \
		"ubi create ${vol} c800000\0" \
	"ubifsargs=set bootargs ubi.mtd=ubi " \
		"root=ubi:rootfs${boot_vol} rootfstype=ubifs\0" \
	"ubifs_mount=ubi part fs;ubifsmount fs:rootfs\0" \
	"ubifs_load=ubifsload ${kernel_addr} ${kernel_fs};" \
		"ubifsload ${dtb_addr} ${dtb_fs};\0" \
	"nand_ubifs=run ubifs_mount ubifs_load ubifsargs addip addcon " \
		"addmtd;bootm ${kernel_addr} - ${dtb_addr}\0" \
	"load_uboot=tftp ${loadaddr} ${u-boot}\0" \
	"load_mlo=tftp ${loadaddr} ${mlo}\0" \
	"update=nandecc sw;nand erase ${uboot_addr} 1E0000;" \
		"nand write ${loadaddr} ${uboot_addr} 1E0000\0" \
	"updatemlo=nandecc hw;nand erase 0 20000;" \
		"nand write ${loadaddr} 0 20000\0" \
	"upd=if run load_uboot;then echo Updating u-boot;if run update;" \
		"then echo U-Boot updated;" \
			"else echo Error updating u-boot !;" \
			"echo Board without bootloader !!;" \
		"fi;" \
		"else echo U-Boot not downloaded..exiting;fi\0" \
	"load_kernel=tftp ${kernel_addr} ${bootfile}\0" \
	"load_dtb=tftp ${dtb_addr} ${dtb}\0" \
	"net_nfs=run load_dtb load_kernel; " \
		"run nfsargs addip addcon addmtd;" \
		"bootz ${kernel_addr} - ${dtb_addr}\0" \
	"delenv=env default -a -f; saveenv; reset\0"

#define CONFIG_BOOTCOMMAND "run nandboot;" \

#define CONFIG_AUTO_COMPLETE	1

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser */
#define CONFIG_SYS_PROMPT		"CastorII # "
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args*/
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
/* memtest works on */
#define CONFIG_SYS_MEMTEST_START (OMAP34XX_SDRC_CS0)
#define CONFIG_SYS_MEMTEST_END	(OMAP34XX_SDRC_CS0 + \
					0x01F00000) /* 31MB */

#define CONFIG_SYS_LOAD_ADDR	(OMAP34XX_SDRC_CS0) /* default load */
								/* address */

/*
 * OMAP3 has 12 GP timers, they can be driven by the system clock
 * (12/13/16.8/19.2/38.4MHz) or by 32KHz clock. We use 13MHz (V_SCLK).
 * This rate is divided by a local divisor.
 */
#define CONFIG_SYS_TIMERBASE	OMAP34XX_GPT2
#define CONFIG_SYS_PTV			2	/* Divisor: 2^(PTV+1) => 8 */
#define CONFIG_SYS_HZ			1000

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS	2	/* CS1 may or may not be populated */
#define PHYS_SDRAM_1			OMAP34XX_SDRC_CS0
#define PHYS_SDRAM_2			OMAP34XX_SDRC_CS1

#define CONFIG_SYS_MONITOR_LEN	(256 << 10)	/* Reserve 2 sectors */

/* Board NAND Info. */
#define CONFIG_SYS_NAND_QUIET_TEST

/* FLASH and environment organization */
#ifdef CONFIG_BOOT_ONENAND
#define PISMO1_ONEN_SIZE		GPMC_SIZE_128M /* Configure the PISMO */

#define CONFIG_SYS_ONENAND_BASE		ONENAND_MAP

#define ONENAND_ENV_OFFSET		0x260000 /* environment starts here */

#define CONFIG_ENV_IS_IN_ONENAND	1
#define CONFIG_ENV_SIZE			(128 << 10) /* Total Size Environment */
#define CONFIG_ENV_ADDR			ONENAND_ENV_OFFSET
#endif

#ifdef CONFIG_BOOT_NAND
#define PISMO1_NAND_SIZE		GPMC_SIZE_128M /* Configure the PISMO */
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_SYS_NAND_BASE		NAND_BASE
#define GPMC_NAND_ECC_LP_x16_LAYOUT	1
#define CONFIG_ENV_OFFSET		0x260000 /* environment starts here */
#define CONFIG_ENV_IS_IN_NAND	        1
#define CONFIG_ENV_SIZE			(128 << 10) /* Total Size Environment */
#define CONFIG_ENV_ADDR			NAND_ENV_OFFSET
#define CONFIG_SYS_MAX_NAND_DEVICE      1 /* Max number of NAND dev*/
#endif

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(1024 << 10)

/* SMSC911x Ethernet */
#if defined(CONFIG_CMD_NET)
#define CONFIG_SMC911X
#define CONFIG_SMC911X_32_BIT
#define CONFIG_SMC911X_BASE	0x2C000000
/* BOOTP fields */
#define CONFIG_BOOTP_SUBNETMASK		0x00000001
#define CONFIG_BOOTP_GATEWAY		0x00000002
#define CONFIG_BOOTP_HOSTNAME		0x00000004
#define CONFIG_BOOTP_BOOTPATH		0x00000010
#endif /* (CONFIG_CMD_NET) */

/*
 * Leave it at 0x80008000 to allow booting new u-boot.bin with X-loader
 * and older u-boot.bin with the new U-Boot SPL.
 */
#define CONFIG_SYS_TEXT_BASE		0x80008000
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_SYS_INIT_RAM_ADDR	0x4020f800
#define CONFIG_SYS_INIT_RAM_SIZE	0x800
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					 CONFIG_SYS_INIT_RAM_SIZE - \
					 GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_CACHELINE_SIZE	64

/* Defines for SPL */
#define CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_NAND_SIMPLE
#define CONFIG_SPL_TEXT_BASE		0x40200800
#define CONFIG_SPL_MAX_SIZE		(54 * 1024)	/* 8 KB for stack */
#define CONFIG_SPL_STACK		LOW_LEVEL_SRAM_STACK

/* move malloc and bss high to prevent clashing with the main image */
#define CONFIG_SYS_SPL_MALLOC_START	0x87000000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x80000
#define CONFIG_SPL_BSS_START_ADDR	0x87080000	/* end of minimum RAM */
#define CONFIG_SPL_BSS_MAX_SIZE		0x80000		/* 512 KB */

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300 /* address 0x60000 */
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS	0x200 /* 256 KB */
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION	1
#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME	"u-boot.img"

#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT

#define CONFIG_SPL_GPIO_SUPPORT
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_OMAP3_ID_NAND
#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/omap-common/u-boot-spl.lds"

#ifdef CONFIG_BOOT_ONENAND
#define CONFIG_SPL_ONENAND_SUPPORT

/* OneNAND boot config */
#define CONFIG_SYS_ONENAND_U_BOOT_OFFS  0x80000
#define CONFIG_SYS_ONENAND_PAGE_SIZE	2048
#define CONFIG_SPL_ONENAND_LOAD_ADDR    0x80000
#define CONFIG_SPL_ONENAND_LOAD_SIZE    \
	(512 * 1024 - CONFIG_SPL_ONENAND_LOAD_ADDR)

#endif

#ifdef CONFIG_BOOT_NAND
#define CONFIG_SPL_NAND_SUPPORT
#define CONFIG_SPL_NAND_BASE
#define CONFIG_SPL_NAND_DRIVERS
#define CONFIG_SPL_NAND_ECC

/* NAND boot config */
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT	64
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128*1024)
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	0
#define CONFIG_SYS_NAND_ECCPOS		{2, 3, 4, 5, 6, 7, 8, 9,\
						10, 11, 12, 13}
#define CONFIG_SYS_NAND_ECCSIZE		512
#define CONFIG_SYS_NAND_ECCBYTES	3
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x80000
#endif

#endif				/* __CASTORII_H */
