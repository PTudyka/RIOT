/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_dyn_boot Dynamic Boot Behaviour
 * @ingroup     sys
 * @brief       Select and deselects module depending on current supply voltage
 *
 * @{
 *
 * @file
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 */

#ifndef DYN_BOOT_RUN_LEVELS_H
#define DYN_BOOT_RUN_LEVELS_H

/* Includes */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Enum of possible run levels for dynamic boot
 */
typedef enum {
    RUN_LEVEL_0,
    RUN_LEVEL_1,
    RUN_LEVEL_2,
    RUN_LEVEL_3,
    RUN_LEVEL_4,
    RUN_LEVEL_5,
    RUN_LEVEL_6,
    RUN_LEVEL_7
} run_level_t;

/*
 * @brief Returns current active run level 
 * 
 * @return run_level_t
 */
run_level_t get_run_level(void);

/*
 * @brief Sets given run level as active run level
 * 
 * @param[in] run_level New active run level
 */
void set_run_level(run_level_t run_level);


#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_RUN_LEVELS_H */
/** @} */
