/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_gpio_measurement Timing Measurements over GPIO Pins
 * @ingroup     sys
 * @brief       Measures Timings over specified GPIO Pins
 *
 * @{
 *
 * @file
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 */

#ifndef GPIO_MEASUREMENT_H
#define GPIO_MEASUREMENT_H

/* Add header includes here */
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Declare the API of the module */

inline void gpio_measurement_init(void)
{
    /* Init GPIO Pins for timing measurements */
    gpio_init(STARTUP_GPIO_PIN, GPIO_OUT);
    gpio_init(MODULES_GPIO_PIN, GPIO_OUT);
    // gpio_set(STARTUP_GPIO_PIN); // active low
    // gpio_toggle(STARTUP_GPIO_PIN);
}

inline void toggle_start_timing(void)
{
    gpio_toggle(STARTUP_GPIO_PIN);
}

inline void toggle_module_timing(void)
{
    gpio_toggle(MODULES_GPIO_PIN);
}

#ifdef __cplusplus
}
#endif

#endif /* GPIO_MEASUREMENT_H */
/** @} */
