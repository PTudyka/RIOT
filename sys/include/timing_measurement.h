/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_timing_measurement Timing Measurement for Modules
 * @ingroup     sys
 * @brief       Measures timings of Modules for Dynamic Boot Behaviour
 *
 * @{
 *
 * @file
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 */

#ifndef TIMING_MEASUREMENT_H
#define TIMING_MEASUREMENT_H

/* Add header includes here */
#include <stdbool.h>
#include "xtimer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Declare the API of the module */

#define MEASUREMENT_MODULES {   \
    MODULE_0 = 0,       \
    MODULE_1,           \
    MODULE_2,           \
    MODULE_TIMINGS_SIZE \
}

typedef enum MEASUREMENT_MODULES timing_modules_t;

void start_module_timing(timing_modules_t module);

void stop_module_timing(timing_modules_t module);

uint32_t get_time_for_module(timing_modules_t module);

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_MEASUREMENT_H */
/** @} */
