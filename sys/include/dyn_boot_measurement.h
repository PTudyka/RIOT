/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_dyn_boot_measurement Dynamic Boot Behaviour - Measurement
 * @ingroup     sys
 * @brief       Measures timings of Modules for Dynamic Boot Behaviour
 *
 * @{
 *
 * @file
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 */

#ifndef DYN_BOOT_MEASUREMENT_H
#define DYN_BOOT_MEASUREMENT_H

/* Add header includes here */
#include "dyn_boot.h"
#include "periph/gpio.h"
#include "xtimer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Declare the API of the module */

typedef struct {
    module_t module;
    timex_t time;
} module_timing_t;

void start_module_timing(module_t module);

void stop_module_timing(module_t module);

timex_t get_time_for_module(module_t module);

timex_t[] get_all_timings();

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_MEASUREMENT_H */
/** @} */
