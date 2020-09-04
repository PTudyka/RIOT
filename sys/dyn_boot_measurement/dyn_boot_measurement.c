/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_dyn_boot_measurement
 * @{
 *
 * @file
 * @brief       Dynamic Boot Behaviour - Measurement implementation
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include "dyn_boot_measurement.h"
#if __has_include("dyn_boot_params.h")
#include "dyn_boot_params.h"
#endif

/* Implementation of the module */

// static const module_timing_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
static timex_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
static timex_t current_module_timings[DYN_BOOT_MODULES_COUNT];

void start_module_timing(module_t module)
{
    // Save current time into var
    xtimer_now_timex(&(current_module_timings[module]));
}

void stop_module_timing(module_t module)
{
    timex_t end_time;
    xtimer_now_timex(&end_time);
    timex_t diff = timex_sub(end_time, current_module_timings[module]);
    MODULE_TIMINGS[module] = timex_add(MODULE_TIMINGS[module], diff);
}


timex_t get_time_for_module(module_t module)
{
    return MODULE_TIMINGS[module];
}

timex_t[] get_all_timings();
{
    return MODULE_TIMINGS;
}