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

void periph_init(void)
{
#ifdef MODULE_PERIPH_INIT
    /* initialize configured I2C devices */
#ifdef MODULE_PERIPH_INIT_I2C
    for (unsigned i = 0; i < I2C_NUMOF; i++) {
        i2c_init(I2C_DEV(i));
    }
    DEBUG("I2C initialized\n");
#endif

    /* initialize configured SPI devices */
#ifdef MODULE_PERIPH_INIT_SPI
    for (unsigned i = 0; i < SPI_NUMOF; i++) {
        spi_init(SPI_DEV(i));
    }
    DEBUG("SPI initialized\n");
#endif

    /* Initialize RTT before RTC to allow for RTT based RTC implementations */
#ifdef MODULE_PERIPH_INIT_RTT
    rtt_init();
    DEBUG("rtt initialized\n");
#endif

    /* Initialize RTC */
#ifdef MODULE_PERIPH_INIT_RTC
    rtc_init();
    DEBUG("rtc initialized\n");
#endif

#ifdef MODULE_PERIPH_INIT_HWRNG
    hwrng_init();
    DEBUG("hwrng initialized\n");
#endif

#ifdef MODULE_PERIPH_INIT_USBDEV
    usbdev_init_lowlevel();
    DEBUG("usbdev initialized\n");
#endif

#if defined(MODULE_PERIPH_INIT_WDT) && WDT_HAS_INIT
    wdt_init();
    DEBUG("wdt initialized\n");
#endif

#endif /* MODULE_PERIPH_INIT */
}
