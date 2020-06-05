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
#include "shell.h"
#include "shell_commands.h"

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif

#define ENABLE_DEBUG (1)
#include "debug.h"

#include "periph/gpio.h"

int toggleGPIO(int argc, char **argv)
{
    /* ... */
    (void)argc;
    (void)argv;

    int value = gpio_read(GPIO_PIN(PORT_C, 10));
    if (value > 0)
    {
        gpio_write(GPIO_PIN(PORT_C, 10), 0);
    }
    else
    {
        gpio_write(GPIO_PIN(PORT_C, 10), 1);
    }
    

    return 0;
}

static const shell_command_t commands[] = {
    { "toggle", "toggles GPIO PIN PC10", toggleGPIO },
    { NULL, NULL, NULL }
};

int main(void)
{
    DEBUG("Jumped into main function\n");

    /* Init GPIO Pins for Module timing measurement */
    gpio_init(GPIO_PIN(PORT_C, 10), GPIO_OUT);  // init Pin PC10
    gpio_write(GPIO_PIN(PORT_C, 10), 0);        // set to LOW before measurement

#ifdef MODULE_NETIF
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
#endif

    (void) puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    // shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
