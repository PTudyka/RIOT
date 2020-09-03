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

#include "board.h"
#include "periph_conf.h"
#include "periph/adc.h"
#include "dyn_boot.h"

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif

// #include "periph/adc.h"

// #define VREFINT_LINE 4
// #define VREFINT_CAL_ADDR 0x1FFF7A2A

// int adc_read(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;

//     // int sample=0;

//     // for (unsigned i = 0; i < ADC_NUMOF; i++) {
//     //     sample = adc_sample(ADC_LINE(i), ADC_RES_12BIT);
//     //     if (sample < 0) {
//     //         printf("ADC_LINE(%u): selected resolution not applicable\n", i);
//     //     } else {
//     //         printf("ADC_LINE(%u): %i\n", i, sample);
//     //     }
//     // }

//     // int adc_result = adc_sample(VREFINT_LINE, ADC_RES_12BIT);
//     // uint32_t cal_factor = (ADC1->CALFACT/* & 0x3F*/);
//     // int cal_factor = *((uint16_t*)VREFINT_CAL_ADDR);
//     // int cal_factor = *((uint16_t*)VREFINT_CAL_ADDR);
//     // printf("cal_factor: %d\n", cal_factor);
//     // printf("adc_sample: %d\n", adc_result);

//     // (void) adc_result;
//     // (void) cal_factor;

//     return 0;
// }


int get_current_run_level(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    run_level_t run_level = get_run_level();
    printf("Run Level: %d\n", run_level);
    // printf("Modules Size: %d\n", MODULE_FLAGS_SIZE);
    auto_select_modules();

    return 0;
}

// static const gpio_t pin0 = GPIO_PIN(PORT_C, 4);
// static const gpio_t pin2 = GPIO_PIN(PORT_C, 5);
// static const gpio_t pin4 = GPIO_PIN(PORT_C, 6);

// int get_gpios(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;

//     // gpio_init(GPIO_PIN(PORT_C, 3), GPIO_IN);
//     // gpio_init(GPIO_PIN(PORT_C, 4), GPIO_IN);
//     // gpio_init(GPIO_PIN(PORT_C, 5), GPIO_IN);
//     // gpio_init(pin0, GPIO_IN_PD);
//     // gpio_init(pin2, GPIO_IN_PD);
//     // gpio_init(pin4, GPIO_IN_PD);

//     int pin0_val = gpio_read(pin0);
//     int pin2_val = gpio_read(pin2);
//     int pin4_val = gpio_read(pin4);
//     // uint8_t pc3 = gpio_read(GPIO_PIN(PORT_C, 3));
//     // uint8_t pc4 = gpio_read(GPIO_PIN(PORT_C, 4));
//     // uint8_t pc5 = gpio_read(GPIO_PIN(PORT_C, 5));

//     unsigned char gpio_bits = 0;
//     gpio_bits |= (gpio_read(pin0) ? 1 : 0);
//     gpio_bits |= (gpio_read(pin2) ? 1 : 0) << 1;
//     gpio_bits |= (gpio_read(pin4) ? 1 : 0) << 2;

//     // printf("PC2: %d, PC3: %d, PC4: %d, PC5: %d\n", pc2, pc3, pc4, pc5);
//     printf("Pin0: %d, Pin2: %d, Pin4: %d\n", pin0_val, pin2_val, pin4_val);
//     printf("Bitmuster: %d\n", gpio_bits);

//     return 0;
// }

static const shell_command_t commands[] = {
    // { "adc_read", "reads all adc lines", adc_read },
    { "run_level", "get current run level", get_current_run_level },
    // { "get_gpios", "get current gpio states for PC4,5,6", get_gpios },
    { NULL, NULL, NULL }
};

int main(void)
{
    // gpio_toggle(MODULES_GPIO_PIN);
    gpio_toggle(MODULES_GPIO_PIN);

#ifdef MODULE_NETIF
    // gpio_toggle(MODULES_GPIO_PIN);
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
    // gpio_toggle(MODULES_GPIO_PIN);
#endif

    // (void) puts("Welcome to RIOT!");
    // (void) puts("t");
    // while(1)
    // {
        
    // }

    /* initialize all available ADC lines */
    // for (unsigned i = 0; i < ADC_NUMOF; i++) {
    //     if (adc_init(ADC_LINE(i)) < 0) {
    //         printf("Initialization of ADC_LINE(%u) failed\n", i);
    //         return 1;
    //     } else {
    //         printf("Successfully initialized ADC_LINE(%u)\n", i);
    //     }
    // }

    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(MODULES_GPIO_PIN);
    
    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(STARTUP_GPIO_PIN);

    // printf("adc_init successfull: %d\n", adc_init(VREFINT_LINE));
    // printf("adc_init successfull: %d\n", adc_init(VREFINT_LINE));

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
