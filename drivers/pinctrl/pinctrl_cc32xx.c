/*
 * Copyright (c) 2022 Vaishnav Achath
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ti_cc32xx_pinctrl

#include <zephyr/drivers/pinctrl.h>

#include <inc/hw_types.h>
#include <driverlib/pin.h>

#define PINNUM_MAX PIN_64
#define PINMODE_MAX PIN_MODE_15

static int pinctrl_c32xx_setmode(uint32_t pin, uint32_t mode, uint32_t type, uint32_t strength)
{
	if (pin > PINNUM_MAX || mode > PINMODE_MAX)
		return -EINVAL;

	PinModeSet(pin, mode);
	PinConfigSet(pin, strength, type);

	return 0;
}

static int pinctrl_c32xx_setdir(uint32_t pin, uint32_t dir)
{
	if (pin > PINNUM_MAX)
		return -EINVAL;

	PinDirModeSet(pin, dir);

	return 0;
}


int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
	int ret;
	ARG_UNUSED(reg);
	printk("here in new driver");

	for (uint8_t i = 0U; i < pin_cnt; i++) {
		ret = pinctrl_c32xx_setmode(pins[i].pin, pins[i].mode, pins[i].type, pins[i].strength);
		if (ret < 0)
			return ret;
		if (pins[i].direction) {
			ret = pinctrl_c32xx_setdir(pins[i].pin, pins[i].direction);
			if (ret < 0)
				return ret;
		}
	}

	return 0;
}
