/*
 * Copyright (C) 2014-2017 Freie Universität Berlin
 *               2015 Lari Lehtomäki
 *               2015 TriaGnoSys GmbH
 *               2016-2017 Inria
 *               2016-2017 OTA keys
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_common_nucleo
 * @{
 *
 * @file
 * @brief       Board initialization code for all Nucleo boards
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 * @author      Lari Lehtomäki <lari@lehtomaki.fi>
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 * @author      Víctor Ariño <victor.arino@triagnosys.com>
 * @author      José Alamos <jialamos@uc.cl>
 * @author      Vincent Dupont <vincent@otakeys.com>
 *
 * @}
 */

#include "board.h"
#include "periph/gpio.h"

#define ENABLE_DEBUG (0)
#include "debug.h"

/**
 * @brief   Post-init routine for Boards-specific settings
 */
__attribute__((weak)) void post_board_init (void)
{
}

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    // DEBUG("CPU initialized\n");

    /* initialization of on-board LEDs
     * NOTE: LED0 must be explicitly enabled as it is also used for SPI_DEV(0) */
#ifdef AUTO_INIT_LED0
    gpio_init(LED0_PIN, GPIO_OUT);
#endif
#ifdef LED1_PIN
    gpio_init(LED1_PIN, GPIO_OUT);
#endif
#ifdef LED2_PIN
    gpio_init(LED2_PIN, GPIO_OUT);
#endif

    // DEBUG("Board LEDs initialized\n")

    post_board_init();

    /* Init GPIO Pins for Module timing measurement */
    // gpio_init(GPIO_PIN(PORT_C, 10), GPIO_OUT);  // init Pin PC10
    // gpio_write(GPIO_PIN(PORT_C, 10), 0);        // set to LOW before measurement
}
