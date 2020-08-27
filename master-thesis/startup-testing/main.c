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

#include "thread.h"

#ifdef MODULE_SHELL
#include "shell.h"
#include "shell_commands.h"
#endif

#include "board.h"

#include "periph/pm.h"

#include "net/netdev.h"
#include "net/netopt.h"
#include "xtimer.h"

#ifdef MODULE_NETIF
#include "net/gnrc.h"
#endif
#ifdef MODULE_GNRC_PKTDUMP
#include "net/gnrc/pktdump.h"
#endif


#include "dyn_boot.h"
#include "periph_conf.h"
#include "periph/adc.h"
#define RES ADC_RES_10BIT
#define LINE 0b11110

int get_supply_voltage(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // Init adc line for bandgap measurement
    // adc_init(LINE);

    // Measure bandgap reference
    // ADMUX |= 0x01;
    uint16_t adc_result = adc_sample(LINE, RES);
    printf("ADC Result: %d\n", adc_result);

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

int get_gpios(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // gpio_init(GPIO_PIN(PORT_C, 2), GPIO_IN);
    gpio_init(GPIO_PIN(PORT_C, 3), GPIO_IN_PD);
    gpio_init(GPIO_PIN(PORT_C, 4), GPIO_IN_PD);
    gpio_init(GPIO_PIN(PORT_C, 5), GPIO_IN_PD);

    // uint8_t pc2 = gpio_read(GPIO_PIN(PORT_C, 2));
    uint8_t pc3 = gpio_read(GPIO_PIN(PORT_C, 3));
    uint8_t pc4 = gpio_read(GPIO_PIN(PORT_C, 4));
    uint8_t pc5 = gpio_read(GPIO_PIN(PORT_C, 5));

    printf("PC3: %d, PC4: %d, PC5: %d\n", pc3, pc4, pc5);

    return 0;
}

static const shell_command_t commands[] = {
    { "get_supply_v", "get supply voltage via ADC", get_supply_voltage },
    { "run_level", "get current run level", get_current_run_level },
    { "get_gpios", "get current gpio states for PC2,3,4,5", get_gpios },
    { NULL, NULL, NULL }
};

int main(void)
{
   gpio_toggle(MODULES_GPIO_PIN);
   
#ifdef MODULE_GNRC_PKTDUMP
//    gpio_toggle(MODULES_GPIO_PIN);
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
//    gpio_toggle(MODULES_GPIO_PIN);
#endif

    // set radio to sleep mode
//    gnrc_netif_t *netif = NULL;
//    if(!(netif = gnrc_netif_iter(netif))) {
//        puts("Unable to find netif");
//    }
//    netopt_state_t target_state = NETOPT_STATE_SLEEP;
////    printf("target_state: %d\n", target_state);
//    int ret = netif->dev->driver->set(netif->dev, NETOPT_STATE, (void *)&target_state, sizeof(netopt_state_t));
//    if (ret == -EINVAL)
//    {
//        puts("Invalid value");
//    }
//    else if (ret == -ENOTSUP)
//    {
//        puts("Opt not configurable for device");
//    }
//    else
//    {
//        printf("Bytes written: %d\n", ret);
//    }
//    while (1)
//    {
//        netopt_state_t state = NETOPT_STATE_OFF;
//        (void) netif->dev->driver->get(netif->dev, NETOPT_STATE, &state, 1);
////        printf("bytes: %d\n", bytes);
//        printf("state: %d\n", state);
//
//        xtimer_sleep(2);
//    }

    // (void) puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];

    // gpio_toggle(STARTUP_GPIO_PIN);
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
