/*
 * Copyright (C) 2017 Freie Universität Berlin
 *               2017 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     drivers_periph_init
 * @{
 *
 * @file
 * @brief       Common static peripheral driver initialization implementation
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 *
 * @}
 */

#define USB_H_USER_IS_RIOT_INTERNAL

#ifdef MODULE_PERIPH_INIT
#ifdef MODULE_PERIPH_INIT_I2C
#include "periph/i2c.h"
#endif
#ifdef MODULE_PERIPH_INIT_SPI
#include "periph/spi.h"
#endif
#ifdef MODULE_PERIPH_INIT_RTC
#include "periph/rtc.h"
#endif
#ifdef MODULE_PERIPH_INIT_RTT
#include "periph/rtt.h"
#endif
#ifdef MODULE_PERIPH_INIT_HWRNG
#include "periph/hwrng.h"
#endif
#ifdef MODULE_PERIPH_INIT_USBDEV
#include "periph/usbdev.h"
#endif
#ifdef MODULE_PERIPH_INIT_WDT
#include "periph/wdt.h"
#endif
#endif /* MODULE_PERIPH_INIT */

#define ENABLE_DEBUG (1)
#include "debug.h"

#include "periph/gpio.h"

void periph_init(void)
{
    /* GPIO Pins on Nucleo-L073rz Board to use, CN7 header (left side of board) */
    gpio_t PC10 = GPIO_PIN(PORT_C, 10);
    gpio_t PC12 = GPIO_PIN(PORT_C, 12);
    gpio_t PA13 = GPIO_PIN(PORT_A, 13);
    gpio_t PA14 = GPIO_PIN(PORT_A, 14);
    gpio_t PA15 = GPIO_PIN(PORT_A, 15);
    // gpio_t PB7  = GPIO_PIN(PORT_B, 7);
    // gpio_t PC13 = GPIO_PIN(PORT_C, 13);
    // gpio_t PC14 = GPIO_PIN(PORT_C, 14);
    // gpio_t PC15 = GPIO_PIN(PORT_C, 15);
    // gpio_t PH0  = GPIO_PIN(PORT_H, 0);
    // gpio_t PH1  = GPIO_PIN(PORT_H, 1);
    // gpio_t PC2  = GPIO_PIN(PORT_C, 2);
    // gpio_t PC3  = GPIO_PIN(PORT_C, 3);

    /* Init GPIO Pins */
    gpio_init(PC10, GPIO_OUT);
    gpio_init(PC12, GPIO_OUT);
    gpio_init(PA13, GPIO_OUT);
    gpio_init(PA14, GPIO_OUT);
    gpio_init(PA15, GPIO_OUT);
    // gpio_init(PB7, GPIO_OUT);
    // gpio_init(PC13, GPIO_OUT);
    // gpio_init(PC14, GPIO_OUT);
    // gpio_init(PC15, GPIO_OUT);
    // gpio_init(PH0, GPIO_OUT);
    // gpio_init(PH1, GPIO_OUT);
    // gpio_init(PC2, GPIO_OUT);
    // gpio_init(PC3, GPIO_OUT);

    /* Set every PIN to LOW, to have a consistent state at startup */
    // gpio_clear(PC10);
    // gpio_clear(PC12);
    // gpio_clear(PA13);
    // gpio_clear(PA14);
    // gpio_clear(PA15);
    // gpio_clear(PB7);
    // gpio_clear(PC13);
    // gpio_clear(PC14);
    // gpio_clear(PC15);
    // gpio_clear(PH0);
    // gpio_clear(PH1);
    // gpio_clear(PC2);
    // gpio_clear(PC3);

#ifdef MODULE_PERIPH_INIT
    /* initialize configured I2C devices */
#ifdef MODULE_PERIPH_INIT_I2C
    gpio_set(PC10);
    for (unsigned i = 0; i < I2C_NUMOF; i++) {
        i2c_init(I2C_DEV(i));
    }
    DEBUG("I2C initialized\n");
    gpio_clear(PC10);
#endif

    /* initialize configured SPI devices */
#ifdef MODULE_PERIPH_INIT_SPI
    gpio_set(PC12);
    for (unsigned i = 0; i < SPI_NUMOF; i++) {
        spi_init(SPI_DEV(i));
    }
    DEBUG("SPI initialized\n");
    gpio_clear(PC12);
#endif

    /* Initialize RTT before RTC to allow for RTT based RTC implementations */
#ifdef MODULE_PERIPH_INIT_RTT
    gpio_set(PA13);
    rtt_init();
    DEBUG("rtt initialized\n");
    gpio_clear(PA13);
#endif

    /* Initialize RTC */
#ifdef MODULE_PERIPH_INIT_RTC
    gpio_set(PA14);
    rtc_init();
    DEBUG("rtc initialized\n");
    gpio_clear(PA14);
#endif

#ifdef MODULE_PERIPH_INIT_HWRNG
    gpio_set(PA15);
    hwrng_init();
    DEBUG("hwrng initialized\n");
    gpio_clear(PA15);
#endif

#ifdef MODULE_PERIPH_INIT_USBDEV
    usbdev_init_lowlevel();
    DEBUG("usbdev initialized\n");
    gpio_set(PB7);
#endif

#if defined(MODULE_PERIPH_INIT_WDT) && WDT_HAS_INIT
    wdt_init();
    DEBUG("wdt initialized\n");
    gpio_set(PC13);
#endif

#endif /* MODULE_PERIPH_INIT */
}
