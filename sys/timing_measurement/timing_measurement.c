/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_timing_measurement
 * @{
 *
 * @file
 * @brief       Timing Measurement for Modules implementation
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include "timing_measurement.h"

/* Save timestamp per module in array */
static uint32_t MODULE_TIMINGS[MODULE_TIMINGS_SIZE];

/* Only one module timing measurement should be active at time */
static uint32_t current_timing = 0;

void start_module_timing(void)
{
    // Save current time into var
    current_timing = xtimer_now_usec();
}

void stop_module_timing(timing_modules_t module)
{
    // Get timestamp for end of module and save difference into array
    uint32_t end_time = xtimer_now_usec();
    MODULE_TIMINGS[module] += end_time - current_timing;
}

uint32_t get_time_for_module(timing_modules_t module)
{
    return MODULE_TIMINGS[module];
}