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

#include "dyn_boot_supply_voltage.h"

/* Implementation of the module */

int set_run_level_adc(void)
{
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

    return 0;
}

// TODO: make GPIO Pins to set run_level abstract (in header e.g.)
void set_run_level_gpio(void)
{
    /* Init GPIO Pins for setting run_level */
    gpio_init(0, GPIO_IN);
    gpio_init(1, GPIO_IN);
    gpio_init(2, GPIO_IN);

    unsigned char gpio_bits = 0;
    gpio_bits |= (gpio_read(0) ? 1 : 0) << 2;
    gpio_bits |= (gpio_read(1) ? 1 : 0) << 1;
    gpio_bits |= (gpio_read(2) ? 1 : 0);

    set_run_level(gpio_bits);
}

void set_run_level_manually(run_level_t run_level)
{
    set_run_level(run_level);
}