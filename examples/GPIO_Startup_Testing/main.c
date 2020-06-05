/*
 * Copyright (C) 2020 IBR
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
 * @brief       Evaluate startup characteristics with GPIO pins
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include "periph/gpio.h"

#include "periph/spi.h"
#include "periph/i2c.h"

#define ENABLE_DEBUG (1)
#include "debug.h"

/*
 * Overwrites weak referenced post_startup() in vectors_cortexm.c (cpu/stm32_common/)
 * Initializes GPIO Pins for tracking module inits (auto_init() in sys/auto_init.c)
 * Measured with Logic Analyzer to get an overview about loaded modules and its order
 */
void post_board_init (void)
{   
    // if (!strcmp(RIOT_BOARD, "nucleo-l073rz"))
    // {
    //     DEBUG("Board is not nucleo-l073rz!\n");
    //     return;
    // }
    DEBUG("Board is nucleo-l073rz, initalize GPIO Pins\n");

    /* GPIO Pins on Nucleo-L073rz Board to use, CN7 header (left side of board) */
    gpio_t PC10 = GPIO_PIN(PORT_C, 10);
    gpio_t PC12 = GPIO_PIN(PORT_C, 12);
    gpio_t PA13 = GPIO_PIN(PORT_C, 13);
    gpio_t PA14 = GPIO_PIN(PORT_C, 14);
    gpio_t PA15 = GPIO_PIN(PORT_C, 15);
    gpio_t PB7  = GPIO_PIN(PORT_B, 7);
    gpio_t PC13 = GPIO_PIN(PORT_C, 13);
    gpio_t PC14 = GPIO_PIN(PORT_C, 14);
    gpio_t PC15 = GPIO_PIN(PORT_C, 15);
    gpio_t PH0  = GPIO_PIN(PORT_H, 0);
    gpio_t PH1  = GPIO_PIN(PORT_H, 1);
    gpio_t PC2  = GPIO_PIN(PORT_C, 2);
    gpio_t PC3  = GPIO_PIN(PORT_C, 3);

    /* Init GPIO Pins */
    gpio_init(PC10, GPIO_OUT);
    gpio_init(PC12, GPIO_OUT);
    gpio_init(PA13, GPIO_OUT);
    gpio_init(PA14, GPIO_OUT);
    gpio_init(PA15, GPIO_OUT);
    gpio_init(PB7, GPIO_OUT);
    gpio_init(PC13, GPIO_OUT);
    gpio_init(PC14, GPIO_OUT);
    gpio_init(PC15, GPIO_OUT);
    gpio_init(PH0, GPIO_OUT);
    gpio_init(PH1, GPIO_OUT);
    gpio_init(PC2, GPIO_OUT);
    gpio_init(PC3, GPIO_OUT);

    /* Set every PIN to LOW, to have a consistent state at startup */
    gpio_clear(PC10);
    gpio_clear(PC12);
    gpio_clear(PA13);
    gpio_clear(PA14);
    gpio_clear(PA15);
    gpio_clear(PB7);
    gpio_clear(PC13);
    gpio_clear(PC14);
    gpio_clear(PC15);
    gpio_clear(PH0);
    gpio_clear(PH1);
    gpio_clear(PC2);
    gpio_clear(PC3);
}

static const shell_command_t commands[] = {
    // { "toggle", "toggles GPIO PIN PC10", toggleGPIO },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("Generated RIOT application: 'GPIO_Startup_Testing'");

    (void) puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    // shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
