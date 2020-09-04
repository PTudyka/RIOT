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
#if __has_include("dyn_boot_params.h")
#include "dyn_boot_params.h"
#endif

/* Implementation of the module */

/* Size of array for saving module flags */
#define MODULE_FLAGS_SIZE ((DYN_BOOT_MODULES_COUNT & 7) == 0 ? (DYN_BOOT_MODULES_COUNT >> 3) : ((DYN_BOOT_MODULES_COUNT >> 3) +1))

/* For each module group, a flag is saved as Bit, if this module group should be loaded */
static module_flag_t MODULE_FLAGS[MODULE_FLAGS_SIZE];

/* Current active run level for determining modules for dyn_boot */
static run_level_t _run_level = RUN_LEVEL_7;

/* Array of modules with specific run_levels, at which these modules should be disabled (added by _params file) */
#ifdef RUN_LEVEL_MODULES
static const run_level_modules_t _RUN_LEVEL_MODULES[] = RUN_LEVEL_MODULES;
static const uint16_t RUN_LEVEL_MODULES_SIZE = (sizeof(_RUN_LEVEL_MODULES) / sizeof(run_level_modules_t));
#endif

#ifdef DYN_BOOT_GPIO_CONF
static const dyn_boot_gpio_t _gpio_config = DYN_BOOT_GPIO_CONF;
#endif

#ifdef DYN_BOOT_ADC_CONF
static const dyn_boot_adc_t _adc_config = DYN_BOOT_ADC_CONF;
#endif

// static const module_timing_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
static timex_t MODULE_TIMINGS[DYN_BOOT_MODULES_COUNT];
static timex_t current_module_timings[DYN_BOOT_MODULES_COUNT];

run_level_t get_run_level(void)
{
    return _run_level;
}

void set_run_level(run_level_t run_level)
{
    _run_level = run_level;
}

bool dyn_boot_get_flag(module_t module)
{
    /*
     * module / 8 to get array index (module >> 3)
     * module % 8 to get bit index (module & 7)
     */
    return (MODULE_FLAGS[module >> 3] & (1 << (module & 7)));
}

/*
 * @brief Inline function to set Flag for a specific module
 * 
 * @param[in] module Module to set flag for
 * @param[in] val Boolean to set flag (true/false)
 */
static inline void _dyn_boot_set_flag(module_t module, bool val)
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

void auto_select_modules(void)
{
    // Fill with 1 at start
    unsigned i;
    for(i=0; i < MODULE_FLAGS_SIZE; ++i)
    {
        MODULE_FLAGS[i] = 0xFF;
    }

#ifdef RUN_LEVEL_MODULES
    // printf("Run_level_modules count: %d\n", RUN_LEVEL_MODULES_SIZE);

    // Deactivate modules depending on run_level
    for (i=0; i < RUN_LEVEL_MODULES_SIZE; ++i)
    {
        // printf("Current run_level: %d, run_level of module: %d\n", _run_level, _RUN_LEVEL_MODULES[i].run_level);

        /* If current run_level is higher than next item in list 
         *  -> higher modules should not be disabled
         *  -> break loop earlier to save time
         */
        if (_run_level > _RUN_LEVEL_MODULES[i].run_level)
        {
            // printf("Break loop\n");
            break;
        }

        // Check if module is valid
        if (_RUN_LEVEL_MODULES[i].module >= DYN_BOOT_MODULES_COUNT)
            continue;

        // Deactive module, if run_level is appropriate and module is valid
        _dyn_boot_set_flag(_RUN_LEVEL_MODULES[i].module, false);
    }
#endif

    // Return count of disabled modules
    // return 0;
}

int set_run_level_adc(void)
{

#ifdef DYN_BOOT_ADC_CONF
    // Measure bandgap reference
    // ADMUX |= 0x01;
    if(adc_init(_adc_config.v_ref_line)/*adc_init(LINE)*/)
    {
        // LOG_ERROR("Init ADC failed!\n");
        return -1;
    }

    // Sample 5 times before "real" measurement
    uint8_t i;
    int adc_result = 0;

    // First values are not good, bandgap voltage reference needs to stabilize
    for (i=0; i < 3; ++i)
    {
        (void) adc_sample(_adc_config.v_ref_line, _adc_config.resolution);
    }
    adc_result = adc_sample(_adc_config.v_ref_line, _adc_config.resolution);
    // (void) adc_result;

    // printf("adc_result: %d\n", adc_result);

    // Set run_level according to adc sample
    if (adc_result > _adc_config.level_1)
    {
        set_run_level(RUN_LEVEL_0);
    }
    else if (adc_result > _adc_config.level_2)
    {
        set_run_level(RUN_LEVEL_1);
    }
    else if (adc_result > _adc_config.level_3)
    {
        set_run_level(RUN_LEVEL_2);
    }
    else if (adc_result > _adc_config.level_4)
    {
        set_run_level(RUN_LEVEL_3);
    }
    else if (adc_result > _adc_config.level_5)
    {
        set_run_level(RUN_LEVEL_4);
    }
    else if (adc_result > _adc_config.level_6)
    {
        set_run_level(RUN_LEVEL_5);
    }
    else if (adc_result > _adc_config.level_7)
    {
        set_run_level(RUN_LEVEL_6);
    }
    else /*if (adc_result > _adc_config.level_7)*/
    {
        set_run_level(RUN_LEVEL_7);
    }

#endif

    return 0;
}

void start_module_timing(module_t module)
{
    // Save current time into var
    xtimer_now_timex(&(current_module_timings[module]));
}

void stop_module_timing(module_t module)
{
    timex_t end_time;
    xtimer_now_timex(&end_time);
    timex_t diff = timex_sub(end_time, current_module_timings[module]);
    MODULE_TIMINGS[module] = timex_add(MODULE_TIMINGS[module], diff);
}

void set_run_level_gpio(void)
{

#ifdef DYN_BOOT_GPIO_CONF
    gpio_init(_gpio_config.GPIO_PIN_0, GPIO_IN_PD);
    gpio_init(_gpio_config.GPIO_PIN_2, GPIO_IN_PD);
    gpio_init(_gpio_config.GPIO_PIN_4, GPIO_IN_PD);

    unsigned char gpio_bits = 0;
    gpio_bits |= (gpio_read(_gpio_config.GPIO_PIN_0) ? 1 : 0);
    gpio_bits |= (gpio_read(_gpio_config.GPIO_PIN_2) ? 1 : 0) << 1;
    gpio_bits |= (gpio_read(_gpio_config.GPIO_PIN_4) ? 1 : 0) << 2;

    set_run_level(gpio_bits);
#endif
}