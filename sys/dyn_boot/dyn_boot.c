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

/* Size of array for saving module flags */
#define MODULE_FLAGS_SIZE ((DYN_BOOT_MODULES_COUNT & 7) == 0 ? (DYN_BOOT_MODULES_COUNT >> 3) : ((DYN_BOOT_MODULES_COUNT >> 3) +1))

/* For each module group, a flag is saved as Bit, if this module group should be loaded */
static module_flags_t MODULE_FLAGS[MODULE_FLAGS_SIZE];

/* Current active run level for determining modules for dyn_boot */
static run_level_t _run_level = RUN_LEVEL_7;

/* Array of modules with specific run_levels, at which these modules should be disabled (added by _params file) */
#ifdef RUN_LEVEL_MODULES
static const run_level_modules_t _run_level_modules[] = RUN_LEVEL_MODULES;
static const uint16_t run_level_modules_count = (sizeof(_run_level_modules) / sizeof(run_level_modules_t));
#endif

run_level_t get_run_level(void)
{
    return _run_level;
}

void set_run_level(run_level_t run_level)
{
    _run_level = run_level;
}

bool dyn_boot_get_flag(modules_t module)
{
    /*
     * module / 8 to get array index (module >> 3)
     * module % 8 to get bit index (module & 7)
     */
    return (MODULE_FLAGS[module >> 3] & (1 << (module & 7)));
}

static inline void _dyn_boot_set_flag(modules_t module, bool val)
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

int auto_select_modules(void)
{
    // Fill with 1 at start
    unsigned i;
    for(i=0; i < MODULE_FLAGS_SIZE; ++i)
    {
        MODULE_FLAGS[i] = 0xFF;
    }

#ifdef RUN_LEVEL_MODULES
    printf("Run_level_modules count: %d\n", run_level_modules_count);

    // Deactivate modules depending on run_level
    for (i=0; i < run_level_modules_count; ++i)
    {
        printf("Current run_level: %d, run_level of module: %d\n", _run_level, _run_level_modules[i].run_level);

        /* If current run_level is higher than next item in list 
         *  -> higher modules should not be disabled
         *  -> break loop earlier to save time
         */
        if (_run_level > _run_level_modules[i].run_level)
        {
            printf("Break loop\n");
            --i;
            break;
        }

        // Check if module is valid
        if (_run_level_modules[i].module >= DYN_BOOT_MODULES_COUNT)
            continue;

        // Deactive module, if run_level is appropriate and module is valid
        _dyn_boot_set_flag(_run_level_modules[i].module, false);
    }
#endif

    // Return count of disabled modules
    return (i+1);
}

int set_run_level_adc(void)
{

#ifndef BOARD_NATIVE
    // Measure bandgap reference
    // ADMUX |= 0x01;
    if(adc_init(LINE))
    {
        // LOG_ERROR("Init ADC failed!\n");
        return -1;
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

    // Set run_level according to adc sample
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
#endif

    return 0;
}

// TODO: make GPIO Pins to set run_level abstract (in header e.g.)
void set_run_level_gpio(void)
{
    /* Init GPIO Pins for setting run_level */
    // gpio_init(0, GPIO_IN);
    // gpio_init(1, GPIO_IN);
    // gpio_init(2, GPIO_IN);

#ifndef BOARD_NATIVE
    gpio_t pin0 = GPIO_PIN(PORT_C, 3);
    gpio_t pin1 = GPIO_PIN(PORT_C, 4);
    gpio_t pin2 = GPIO_PIN(PORT_C, 5);
    gpio_init(pin0, GPIO_IN_PD);
    gpio_init(pin1, GPIO_IN_PD);
    gpio_init(pin2, GPIO_IN_PD);

    unsigned char gpio_bits = 0;
    gpio_bits |= (gpio_read(pin0) ? 1 : 0) << 2;
    gpio_bits |= (gpio_read(pin1) ? 1 : 0) << 1;
    gpio_bits |= (gpio_read(pin2) ? 1 : 0);

    set_run_level(gpio_bits);
#else
    set_run_level(RUN_LEVEL_7);
#endif
}