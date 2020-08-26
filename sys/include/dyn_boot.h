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

#ifndef DYN_BOOT_H
#define DYN_BOOT_H

/* Add header includes here */
// #define MODULES_LIST ED
// #ifndef MODULES_LIST
// #define MODULES_LIST "NO MODULES"
// // #else
// // #define MODULES_LIST "YES MODULES"
// #endif
#include <stdio.h>
#include <stdbool.h>

// #include "dyn_boot_run_levels.h"

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

// Datatype for saving module flag information
typedef unsigned char module_flags_t;

// Create enum with every used module
typedef enum {
    /*
     * Modules
     */
#ifdef MODULE_GNRC 
/*|| MODULE_GNRC_PKTBUF || MODULE_GNRC_PKTDUMP || \
        MODULE_GNRC_SIXLOWPAN || MODULE_GNRC_IPV6 || MODULE_GNRC_UDP || \
        MODULE_GNRC_TCP || MODULE_AUTO_INIT_GNRC_NETIF || \
        MODULE_GNRC_UHCPC || MODULE_AUTO_INIT_GNRC_RPL || \
        MODULE_GNRC_RPL  
*/
    DYN_BOOT_GNRC,
#endif
#ifdef MODULE_PS
    DYN_BOOT_MODULE_PS,
#endif
#ifdef MODULE_SAUL
    DYN_BOOT_MODULE_SAUL,
#endif
#ifdef MODULE_PRNG
    DYN_BOOT_MODULE_PRNG,
#endif
#ifdef MODULE_PERIPH_HWRNG
    DYN_BOOT_MODULE_HWRNG,
#endif
#ifdef MODULE_PERIPH_PM
    DYN_BOOT_MODULE_PM,
#endif
#ifdef MODULE_PERIPH_UART
    DYN_BOOT_MODULE_UART,
#endif
#ifdef MODULE_RANDOM
    DYN_BOOT_MODULE_RANDOM,
#endif
#ifdef MODULE_SHELL
    DYN_BOOT_MODULE_SHELL,
#endif
#ifdef MODULE_ADXL345
    DYN_BOOT_MODULE_ADXL345,
#endif
#ifdef MODULE_BMP180
    DYN_BOOT_MODULE_BMP180,
#endif
#ifdef MODULE_L3G4200D
    DYN_BOOT_MODULE_L3G4200D,
#endif
#ifdef MODULE_XTIMER
    DYN_BOOT_MODULE_XTIMER,
#endif

    /*
     * Peripherals
     */
#ifdef MODULE_PERIPH_I2C
    DYN_BOOT_PERIPH_I2C,
#endif
#ifdef MODULE_PERIPH_SPI
    DYN_BOOT_PERIPH_SPI,
#endif
#ifdef MODULE_PERIPH_RTC
    DYN_BOOT_PERIPH_RTC,
#endif

    // End type to get length of enum
    DYN_BOOT_MODULES_COUNT
} dyn_boot_modules_t;

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

/*
 * @brief Returns flag for given module. Determines, if module should be initialized or not.
 * 
 * @param[in] module Module to get flag for
 * @return 0, if module should not be loaded. 1 if module should be loaded.
 */
bool dyn_boot_get_flag(dyn_boot_modules_t module);

/*
 * Determines at current run_level, which modules should be initialized.
 * Sets module flags accordingly.
 */
int auto_select_modules(void);

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_H */
/** @} */
