/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_dyn_boot
 * @{
 *
 * @file
 * @brief       Dynamic Boot Behaviour implementation
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include "dyn_boot.h"

/* Implementation of the module */
#define MODULE_FLAGS_SIZE ((DYN_BOOT_MODULES_COUNT & 7) == 0 ? (DYN_BOOT_MODULES_COUNT >> 3) : ((DYN_BOOT_MODULES_COUNT >> 3) +1))
module_flags_t MODULE_FLAGS[MODULE_FLAGS_SIZE];

#ifdef BOARD_INGA_RED
#define ADC_3_3_V   342
#define ADC_3_0_V   376
#define ADC_2_7_V   418
#define ADC_2_4_V   470
#define ADC_2_1_V   537
#else
#define ADC_3_3_V   0xFFFF
#define ADC_3_0_V   0xFFFF
#define ADC_2_7_V   0xFFFF
#define ADC_2_4_V   0xFFFF
#define ADC_2_1_V   0xFFFF
#endif

bool dyn_boot_get_flag(dyn_boot_modules_t module)
{
    /*
     * module / 8 to get array index (module >> 3)
     * module % 8 to get bit index (module & 7)
     */
    return (MODULE_FLAGS[module >> 3] & (1 << (module & 7)));
}

static inline void _dyn_boot_set_flag(dyn_boot_modules_t module, bool val)
{
    if (val)
    {
        MODULE_FLAGS[module >> 3] |= (1 << (module & 7));
    }
    else
    {
        MODULE_FLAGS[module >> 3] &= ~(1 << (module & 7));
    }
}

static inline uint16_t _get_supply_voltage_adc(void)
{
    // Measure bandgap reference
    // ADMUX |= 0x01;
    if(adc_init(LINE))
    {
        // LOG_ERROR("Init ADC failed!\n");
        return 0xFFFF;
    }

    // Sample 5 times before "real" measurement
    uint8_t i;
    uint16_t adc_result = 0;

    // First values are not good, bandgap voltage reference needs to stabilize
    for (i=0; i < 3; ++i)
    {
        (void) adc_sample(LINE, RES);
    }
    adc_result = adc_sample(LINE, RES);

    if(adc_result > ADC_3_3_V)
    {
        set_run_level(RUN_LEVEL_3);
    }
    if(adc_result > ADC_3_0_V)
    {
        set_run_level(RUN_LEVEL_2);
    }
    if(adc_result > ADC_2_7_V)
    {
        set_run_level(RUN_LEVEL_1);
    }
    if(adc_result > ADC_2_4_V)
    {
        set_run_level(RUN_LEVEL_0);
    }

    return adc_result;
}

int auto_select_modules(void)
{
    // uint16_t supply_v_adc = _get_supply_voltage();

    run_level_t run_level = get_run_level();

    // printf("MODULE_FLAGS size: %d\n", DYN_BOOT_MODULES_COUNT >> 3);
    // printf("Modules Count: %d\n", DYN_BOOT_MODULES_COUNT);
    // printf("Calculated Count: %d\n", MODULE_FLAGS_SIZE);

    // Fill with 1 at start
    unsigned i;
    for(i=0; i < MODULE_FLAGS_SIZE; ++i)
    {
        MODULE_FLAGS[i] = 0xFF;
        // printf("MODULES_FLAGS: %d\n", MODULE_FLAGS[i]);
    }
    // (void) puts(MODULES_LIST);
    // const char *modules = MODULES_LIST;
    // (void) puts(modules);

    // Disable modules at different voltages
    // printf("ADC Result: %d\n", supply_v_adc);
    // if(supply_v_adc > ADC_3_3_V)
    // {
    //     _dyn_boot_set_flag(DYN_BOOT_MODULE_ADXL345, false);
    // }
    // if(supply_v_adc > ADC_3_0_V)
    // {
    //     _dyn_boot_set_flag(DYN_BOOT_MODULE_BMP180, false);
    // }
    // if(supply_v_adc > ADC_2_7_V)
    // {
    //     _dyn_boot_set_flag(DYN_BOOT_MODULE_L3G4200D, false);
    // }
    // if(supply_v_adc > ADC_2_4_V)
    // {
    //     _dyn_boot_set_flag(DYN_BOOT_GNRC, false);
    // }

    switch (run_level)
    {
        case RUN_LEVEL_0:
            _dyn_boot_set_flag(DYN_BOOT_GNRC, false);
            // fall through
        case RUN_LEVEL_1:
            _dyn_boot_set_flag(DYN_BOOT_MODULE_L3G4200D, false);
            // fall through
        case RUN_LEVEL_2:
            _dyn_boot_set_flag(DYN_BOOT_MODULE_BMP180, false);
            // fall through
        case RUN_LEVEL_3:
            _dyn_boot_set_flag(DYN_BOOT_MODULE_ADXL345, false);
            // fall through
        case RUN_LEVEL_4:
            // fall through
        case RUN_LEVEL_5:
            // fall through
        case RUN_LEVEL_6:
            // fall through
        case RUN_LEVEL_7:
            // Deactivate nothing
            break;
    }

    /*
     * Deactivate SAUL, if not a single sensor is activated
     */
    // bool sensor_count = (MODULE_FLAGS[0] > 0x00);
    // if (dyn_boot_get_flag)

    // _dyn_boot_set_flag(DYN_BOOT_MODULE_SAUL, sensor_count);

    return -1;
}

// void toggle_flag(void)
// {
//     // char val = MODULE_FLAGS[0];
//     if (MODULE_FLAGS)
//     {
//         MODULE_FLAGS = 0x00;
//     }
//     else
//     {
//         MODULE_FLAGS = 0x01;
//     }
// }