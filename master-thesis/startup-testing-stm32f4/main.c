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

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif

int adc_read(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    int sample=0;

    for (unsigned i = 0; i < ADC_NUMOF; i++) {
        sample = adc_sample(ADC_LINE(i), ADC_RES_12BIT);
        if (sample < 0) {
            printf("ADC_LINE(%u): selected resolution not applicable\n", i);
        } else {
            printf("ADC_LINE(%u): %i\n", i, sample);
        }
    }

    return 0;
}

static const shell_command_t commands[] = {
    { "adc_read", "reads all adc lines", adc_read },
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
    for (unsigned i = 0; i < ADC_NUMOF; i++) {
        if (adc_init(ADC_LINE(i)) < 0) {
            printf("Initialization of ADC_LINE(%u) failed\n", i);
            return 1;
        } else {
            printf("Successfully initialized ADC_LINE(%u)\n", i);
        }
    }

    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(MODULES_GPIO_PIN);
    
    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(MODULES_GPIO_PIN);
    // gpio_toggle(STARTUP_GPIO_PIN);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
