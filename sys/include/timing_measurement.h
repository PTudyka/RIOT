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

#include <stdbool.h>

/* Relevant for saving timestamps */
#include "xtimer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Extend this, if more Modules should be used */
#define MEASUREMENT_MODULES {   \
    MODULE_0 = 0,       \
    MODULE_1,           \
    MODULE_2,           \
    MODULE_TIMINGS_SIZE \
}

/* Enum to differentiate between timestamp of different modules */
typedef enum MEASUREMENT_MODULES timing_modules_t;

/*
 * @brief Saves current timestamp to indicate start of module measurement
 */
void start_module_timing(void);

/*
 * @brief Gets current timestamp (end of module) and saves difference
 * between start and end for the given module
 * 
 * @param[in] module Module to save timing for
 */
void stop_module_timing(timing_modules_t module);

/*
 * @brief Get timing of given module
 * 
 * @return Timing in usecs for given module
 */
uint32_t get_time_for_module(timing_modules_t module);

#ifdef __cplusplus
}
#endif

#endif /* TIMING_MEASUREMENT_H */
/** @} */
