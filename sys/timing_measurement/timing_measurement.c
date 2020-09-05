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

/* Implementation of the module */

// static const module_timing_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
static uint32_t MODULE_TIMINGS[MODULE_TIMINGS_SIZE];
// static uint64_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
// static uint64_t current_module_timings[DYN_BOOT_MODULES_COUNT];

// static bool is_init = false;
static uint32_t current_timing = 0;

void start_module_timing(timing_modules_t module)
{
    (void) module;
    // if (!is_init)
    // {
    //     xtimer_init();
    //     is_init = true;
    // }

    // Save current time into var
    // xtimer_now_timex(&(current_module_timings[module]));
    current_timing = xtimer_now_usec();

    // current_module_timings[module] = xtimer_now_usec64();
}

void stop_module_timing(timing_modules_t module)
{
    // if (!is_init)
    // {
    //     xtimer_init();
    //     is_init = true;
    // }

    // timex_t end_time;
    // xtimer_now_timex(&end_time);
    // timex_t diff = timex_sub(end_time, current_module_timings[module]);
    // MODULE_TIMINGS[module] = timex_add(MODULE_TIMINGS[module], diff);

    uint32_t end_time = xtimer_now_usec();
    MODULE_TIMINGS[module] += end_time - current_timing;

    // uint64_t end_time = xtimer_now_usec64();
    // MODULE_TIMINGS[module] = end_time - current_module_timings[module];
}

uint32_t get_time_for_module(timing_modules_t module)
{
    // return MODULE_TIMINGS[module];
    return MODULE_TIMINGS[module];
}

// timex_t[] get_all_timings();
// {
//     return MODULE_TIMINGS;
// }