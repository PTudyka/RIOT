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

#ifndef DYN_BOOT_SUPPLY_VOLTAGE_H
#define DYN_BOOT_SUPPLY_VOLTAGE_H

/* Includes */
#include "dyn_boot.h"

#include "log.h"
#include "periph_conf.h"
#include "periph/adc.h"

/* Defines */
#ifdef BOARD_INGA_RED
#define ADC_3_3_V   342
#define ADC_3_0_V   376
#define ADC_2_7_V   418
#define ADC_2_4_V   470
#define ADC_2_1_V   537

#define RES ADC_RES_10BIT
#define LINE 0b11110
#else
#define ADC_3_3_V   0xFFFF
#define ADC_3_0_V   0xFFFF
#define ADC_2_7_V   0xFFFF
#define ADC_2_4_V   0xFFFF
#define ADC_2_1_V   0xFFFF

#define RES (0)
#define LINE (-1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// TODO: needs adjustement, maybe not sufficient for all three boards
/*
 * @brief Sets current run_level according to adc measurement (bandgap reference)
 * 
 * @return 0 on success
 */
int set_run_level_adc(void);

/*
 * @brief Sets run_level according to given gpio pin pattern. Useful for evaluation.
 * 
 * @param[in] gpio_pins Given gpio pin pattern (3 Pins -> 8 possible values)
 */
void set_run_level_gpio(unsigned char gpio_pins);

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_SUPPLY_VOLTAGE_H */
/** @} */
