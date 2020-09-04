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
 * Define which Modules to deactivate at specific run_level
 * Sorted descending from highest run_level
 * Example list:
 * {
 *  { RUN_LEVEL_7, DYN_BOOT_MODULE_PS },        \
 *  { RUN_LEVEL_5, DYN_BOOT_MODULE_RANDOM },    \
 *  { RUN_LEVEL_3, DYN_BOOT_MODULE_SAUL },      \
 *  { RUN_LEVEL_3, DYN_BOOT_GNRC },             \
 *  { RUN_LEVEL_0, MODULE_SHELL }               \
 * }
 * 
 * Define Configuration to get V_Ref supply voltage via ADC
 * struct: {
 *  line;
 *  res;
 *  level0;
 *  ...
 *  level7;
 * }
 * 
 * Define Configuration to get run_level via GPIO Pins
 * struct: {
 *  pin0;
 *  pin2;
 *  pin4;
 * }
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


#ifdef BOARD_INGA_RED
#define RUN_LEVEL_MODULES {         \
    { RUN_LEVEL_6, DYN_BOOT_MODULE_PRNG }, \
    { RUN_LEVEL_3, DYN_BOOT_MODULE_ADXL345 }, \
    { RUN_LEVEL_3, DYN_BOOT_MODULE_BMP180 }, \
    { RUN_LEVEL_3, DYN_BOOT_MODULE_L3G4200D }, \
    { RUN_LEVEL_2, DYN_BOOT_MODULE_GNRC }  \
}
// TODO: define array size as macro or will it be calculated at compile time?
// #define RUN_LEVEL_MODULES_SIZE (1)

// #define ADC_3_3_V   342
// #define ADC_3_1_V   360
// #define ADC_2_9_V   388
// #define ADC_2_7_V   417
// #define ADC_2_5_V   450
// #define ADC_2_3_V   489
// #define ADC_2_1_V   536
// #define ADC_1_9_V   574
// #define LEVEL_7_ADC 340 // 3,3V as Maximum
#define LEVEL_0_ADC 549 // 1.9 V on HCS-3600
#define LEVEL_1_ADC 522 // 2.0 V on HCS-3600
#define LEVEL_2_ADC 478 // 2.2 V on HCS-3600
#define LEVEL_3_ADC 439 // 2.4 V on HCS-3600
#define LEVEL_4_ADC 406 // 2.6 V on HCS-3600
#define LEVEL_5_ADC 377 // 2.8 V on HCS-3600
#define LEVEL_6_ADC 359 // 3.0 V on HCS-3600
#define LEVEL_7_ADC 345 // 3.2 V on HCS-3600
// #define LEVEL_7_ADC 339 // 3.3 V on HCS-3600
#define RES ADC_RES_10BIT
#define LINE 0b11110

/*
#define DYN_BOOT_ADC_CONF {     \
    LINE,       \
    RES,        \
    ADC_1_9_V,  \
    ADC_2_1_V,  \
    ADC_2_3_V,  \
    ADC_2_5_V,  \
    ADC_2_7_V,  \
    ADC_2_9_V,  \
    ADC_3_1_V,  \
    ADC_3_3_V   \
}
*/
#define DYN_BOOT_ADC_CONF {     \
    LINE,       \
    RES,        \
    LEVEL_0_ADC,  \
    LEVEL_1_ADC,  \
    LEVEL_2_ADC,  \
    LEVEL_3_ADC,  \
    LEVEL_4_ADC,  \
    LEVEL_5_ADC,  \
    LEVEL_6_ADC,  \
    LEVEL_7_ADC   \
}

/*
#define DYN_BOOT_GPIO_CONF {    \
    GPIO_PIN(PORT_C, 3),   \
    GPIO_PIN(PORT_C, 4),    \
    GPIO_PIN(PORT_C, 5)     \
}
*/

#endif /* BOARD_INGA_RED */

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_PARAMS_H */
/** @} */
