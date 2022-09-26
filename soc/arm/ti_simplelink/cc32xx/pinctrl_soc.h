/*
 * Copyright (c) 2022 Vaishnav Achath
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TI_SIMPLELINK_CC32XX_SOC_PINCTRL_H_
#define TI_SIMPLELINK_CC32XX_SOC_PINCTRL_H_

#include <zephyr/types.h>

/* Pin drive strength defines */
#define PIN_STRENGTH_2MA  0x00000020
#define PIN_STRENGTH_4MA  0x00000040
#define PIN_STRENGTH_6MA  0x00000060

/* Pin pull mode defines */
#define PIN_TYPE_OD       0x00000010
#define PIN_TYPE_PU   0x00000100
#define PIN_TYPE_PD   0x00000200

/* Pin direction mode defines */
#define PIN_DIR_MODE_IN  0x00000C00
#define PIN_DIR_MODE_OUT 0x00000800

typedef struct pinctrl_soc_pin {
	uint32_t pin;
	uint32_t mode;
	uint32_t type;
	uint32_t strength;
	uint32_t direction;
} pinctrl_soc_pin_t;

/* Convert DT params to SoC flags */
#define CC32XX_PIN_DRIVE_FLAGS(node_id) \
	(DT_PROP(node_id, drive_strength) << 8)

#define CC32XX_PIN_TYPE_FLAGS(node_id) \
	(DT_PROP(node_id, bias_pull_up) * PIN_TYPE_PU | \
	DT_PROP(node_id, bias_pull_down) * PIN_TYPE_PD | \
	DT_PROP(node_id, drive_open_drain) * PIN_TYPE_OD)

#define CC32XX_PIN_DIRECTION_FLAGS(node_id) \
	(DT_PROP(node_id, input_enable) * PIN_DIR_MODE_IN | \
	DT_PROP(node_id, output_enable) * PIN_DIR_MODE_OUT)

#define CC32XX_DT_PIN(node_id)					\
	{							\
		.pin = DT_PROP_BY_IDX(node_id, pinmux, 0),	\
		.mode = DT_PROP_BY_IDX(node_id, pinmux, 1),	\
		.strength = CC32XX_PIN_DRIVE_FLAGS(node_id), \
		.type = CC32XX_PIN_DRIVE_FLAGS(node_id), \
		.direction = CC32XX_PIN_DIRECTION_FLAGS(node_id) \
	},

#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx)		\
	CC32XX_DT_PIN(DT_PROP_BY_IDX(node_id, prop, idx))

#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop)		\
	{ DT_FOREACH_PROP_ELEM(node_id, prop, Z_PINCTRL_STATE_PIN_INIT) }

#endif /* TI_SIMPLELINK_CC32XX_SOC_PINCTRL_H_ */
