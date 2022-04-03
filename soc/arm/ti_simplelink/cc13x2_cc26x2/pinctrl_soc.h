/*
 * Copyright (c) 2022 Vaishnav Achath
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TI_SIMPLELINK_CC13XX_CC26XX_SOC_PINCTRL_H_
#define TI_SIMPLELINK_CC13XX_CC26XX_SOC_PINCTRL_H_

#include <zephyr/types.h>

typedef struct pinctrl_soc_pin_t {
	uint32_t pin;
	uint32_t iofunc;
	uint32_t iomode;
} pinctrl_soc_pin_t;

#define CC13XX_CC26XX_DT_PIN(node_id)					\
	{							\
		.pin = DT_PROP_BY_IDX(node_id, pinmux, 0),	\
		.iofunc = DT_PROP_BY_IDX(node_id, pinmux, 1),	\
		.iomode = DT_PROP_BY_IDX(node_id, pinmux, 2)	\
	},

#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx)		\
	CC13XX_CC26XX_DT_PIN(DT_PROP_BY_IDX(node_id, prop, idx))

#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop)		\
	{ DT_FOREACH_PROP_ELEM(node_id, prop, Z_PINCTRL_STATE_PIN_INIT) }

#endif /* TI_SIMPLELINK_CC13XX_CC26XX_SOC_PINCTRL_H_ */
