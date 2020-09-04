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

#ifndef DYN_BOOT_PARAMS_H
#define DYN_BOOT_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Define which Modules to deactivate at specific run_level
 * 
 * Sorted descending from highest run_level
 * 
 * Example list:
 * {
 *  { RUN_LEVEL_7, DYN_BOOT_MODULE_PS },        \
 *  { RUN_LEVEL_5, DYN_BOOT_MODULE_RANDOM },    \
 *  { RUN_LEVEL_3, DYN_BOOT_MODULE_SAUL },      \
 *  { RUN_LEVEL_3, DYN_BOOT_GNRC },             \
 *  { RUN_LEVEL_0, MODULE_SHELL }               \
 * }
 *  
 */
#define RUN_LEVEL_MODULES {         \
    { RUN_LEVEL_0, DYN_BOOT_MODULE_GNRC }  \
}
// TODO: define array size as macro or will it be calculated at compile time?
// #define RUN_LEVEL_MODULES_SIZE (1)

/*
 * Define Configuration to get V_Ref supply voltage via ADC
 * struct: {
 *  line;
 *  res;
 *  level0;
 *  ...
 *  level7;
 * }
 */
#define DYN_BOOT_ADC_CONF {     \
    0,  \
    0,  \
    0,  \
    0,  \
    0,  \
    0,  \
    0,  \
    0,  \
    0,  \
    0   \
}

/*
 * Define Configuration to get run_level via GPIO Pins
 * struct: {
 *  pin0;
 *  pin2;
 *  pin4;
 * }
 */
#define DYN_BOOT_GPIO_CONF {    \
    GPIO_PIN(0, 0),             \
    GPIO_PIN(0, 0),             \
    GPIO_PIN(0, 0)              \
}

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_PARAMS_H */
/** @} */
