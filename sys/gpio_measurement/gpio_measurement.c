/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_gpio_measurement
 * @{
 *
 * @file
 * @brief       Timing Measurements over GPIO Pins implementation
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include "gpio_measurement.h"

/* Implementation of the module */

extern inline void gpio_measurement_init(void);

extern inline void toggle_module_timing(void);

extern inline void toggle_start_timing(void);
