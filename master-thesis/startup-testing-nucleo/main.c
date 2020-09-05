/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#ifdef MODULE_SHELL
#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#endif

#include "xtimer.h"

#include "board.h"

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif

#include "dyn_boot.h"
#include "periph/gpio.h"
#include "periph/adc.h"

#ifdef MODULE_TIMING_MEASUREMENT
#include "timing_measurement.h"
#endif

#define VREFINT_CAL_ADDR 0x1FF80078

int adc_read(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // int sample=0;

    // for (unsigned i = 0; i < ADC_NUMOF; i++) {
    //     sample = adc_sample(ADC_LINE(i), ADC_RES_12BIT);
    //     if (sample < 0) {
    //         printf("ADC_LINE(%u): selected resolution not applicable\n", i);
    //     } else {
    //         printf("ADC_LINE(%u): %i\n", i, sample);
    //     }
    // }

    int adc_result = adc_sample(6, ADC_RES_12BIT);
    // uint32_t cal_factor = (ADC1->CALFACT/* & 0x3F*/);
    uint32_t cal_factor = *((uint16_t*)VREFINT_CAL_ADDR);
    printf("cal_factor: %lu\n", cal_factor);
    printf("adc_sample: %d\n", adc_result);

    return 0;
}

int get_current_run_level(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    run_level_t run_level = get_run_level();
    printf("Run Level: %d\n", run_level);

    return 0;
}

static const gpio_t pin0 = GPIO_PIN(PORT_C, 11);
static const gpio_t pin2 = GPIO_PIN(PORT_C, 8);
static const gpio_t pin4 = GPIO_PIN(PORT_C, 6);

int get_gpios(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // gpio_init(GPIO_PIN(PORT_C, 3), GPIO_IN);
    // gpio_init(GPIO_PIN(PORT_C, 4), GPIO_IN);
    // gpio_init(GPIO_PIN(PORT_C, 5), GPIO_IN);
    // gpio_init(pin0, GPIO_IN_PD);
    // gpio_init(pin2, GPIO_IN_PD);
    // gpio_init(pin4, GPIO_IN_PD);

    int pin0_val = gpio_read(pin0);
    int pin2_val = gpio_read(pin2);
    int pin4_val = gpio_read(pin4);
    // uint8_t pc3 = gpio_read(GPIO_PIN(PORT_C, 3));
    // uint8_t pc4 = gpio_read(GPIO_PIN(PORT_C, 4));
    // uint8_t pc5 = gpio_read(GPIO_PIN(PORT_C, 5));

    unsigned char gpio_bits = 0;
    gpio_bits |= (gpio_read(pin0) ? 1 : 0);
    gpio_bits |= (gpio_read(pin2) ? 1 : 0) << 1;
    gpio_bits |= (gpio_read(pin4) ? 1 : 0) << 2;

    // printf("PC2: %d, PC3: %d, PC4: %d, PC5: %d\n", pc2, pc3, pc4, pc5);
    printf("Pin0: %d, Pin2: %d, Pin4: %d\n", pin0_val, pin2_val, pin4_val);
    printf("Bitmuster: %d\n", gpio_bits);

    return 0;
}

int get_ts(int argc, char **argv)
{
    (void) argc;
    (void) argv;

#ifdef MODULE_TIMING_MEASUREMENT
    start_module_timing();
    printf("This test message will be measured (timing)\n");
    stop_module_timing(MODULE_0);

    printf("Module timing for thread creations: %lu us\n", get_time_for_module(MODULE_0));
#endif

    return 0;
}

static const shell_command_t commands[] = {
    { "adc_read", "reads all adc lines", adc_read },
    { "run_level", "get current run level", get_current_run_level },
    { "get_gpios", "get current gpio states", get_gpios },
    { "get_ts", "get module timing for radio init", get_ts },
    { NULL, NULL, NULL }
};

int main(void)
{
    // gpio_toggle(STARTUP_GPIO_PIN);
    gpio_toggle(MODULES_GPIO_PIN);

#ifdef MODULE_NETIF
    // gpio_toggle(MODULES_GPIO_PIN);
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
    // gpio_toggle(MODULES_GPIO_PIN);
#endif

    // (void) puts("Welcome to RIOT!");

    // int i=0;
    // while(1)
    // {
    //     // i+= 1;
    // }

    // printf("%d", i);

    adc_init(6);

    // printf("gpio_init success: %d\n", gpio_init(pin0, GPIO_IN_PD));
    // printf("gpio_init success: %d\n", gpio_init(pin2, GPIO_IN_PD));
    // printf("gpio_init success: %d\n", gpio_init(pin4, GPIO_IN_PD));

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    
    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(MODULES_GPIO_PIN);
    gpio_toggle(MODULES_GPIO_PIN);
    // // gpio_toggle(STARTUP_GPIO_PIN);
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
