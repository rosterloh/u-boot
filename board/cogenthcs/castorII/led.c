/*
 * Copyright (c) 2010 Texas Instruments, Inc.
 * Jason Kridner <jkridner@beagleboard.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <status_led.h>
#include <asm/arch/cpu.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>

/* GPIO pins for the LEDs */
#define CASTORII_NORMAL_LED 95
#define CASTORII_FAILURE_LED 104

#ifdef STATUS_LED_GREEN
void green_led_off(void)
{
	__led_set (STATUS_LED_GREEN, 0);
}

void green_led_on(void)
{
	__led_set (STATUS_LED_GREEN, 1);
}
#endif

void __led_init (led_id_t mask, int state)
{
	__led_set (mask, state);
}

void __led_toggle (led_id_t mask)
{
	int state, toggle_gpio = 0;
#ifdef STATUS_LED_BIT
	if (!toggle_gpio && STATUS_LED_BIT & mask)
		toggle_gpio = CASTORII_NORMAL_LED;
#endif
#ifdef STATUS_LED_BIT1
	if (!toggle_gpio && STATUS_LED_BIT1 & mask)
		toggle_gpio = CASTORII_FAILURE_LED;
#endif
	if (toggle_gpio) {
		if (!gpio_request(toggle_gpio, "")) {
			gpio_direction_output(toggle_gpio, 0);
			state = gpio_get_value(toggle_gpio);
			gpio_set_value(toggle_gpio, !state);
		}
	}
}

void __led_set (led_id_t mask, int state)
{
#ifdef STATUS_LED_BIT
	if (STATUS_LED_BIT & mask) {
		if (!gpio_request(CASTORII_NORMAL_LED, "")) {
			gpio_direction_output(CASTORII_NORMAL_LED, 0);
			gpio_set_value(CASTORII_NORMAL_LED, state);
		}
	}
#endif
#ifdef STATUS_LED_BIT1
	if (STATUS_LED_BIT1 & mask) {
		if (!gpio_request(CASTORII_FAILURE_LED, "")) {
			gpio_direction_output(CASTORII_FAILURE_LED, 0);
			gpio_set_value(CASTORII_FAILURE_LED, state);
		}
	}
#endif
}
