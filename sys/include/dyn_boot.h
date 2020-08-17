/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_dyn_boot Dynamic Boot Behaviour
 * @ingroup     sys
 * @brief       Select and deselects module depending on current supply voltage
 *
 * @{
 *
 * @file
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 */

#ifndef DYN_BOOT_H
#define DYN_BOOT_H

/* Add header includes here */
// #define MODULES_LIST ED
// #ifndef MODULES_LIST
// #define MODULES_LIST "NO MODULES"
// // #else
// // #define MODULES_LIST "YES MODULES"
// #endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

    /*
     * Modules
     */
#ifdef MODULE_GNRC 
/*|| MODULE_GNRC_PKTBUF || MODULE_GNRC_PKTDUMP || \
        MODULE_GNRC_SIXLOWPAN || MODULE_GNRC_IPV6 || MODULE_GNRC_UDP || \
        MODULE_GNRC_TCP || MODULE_AUTO_INIT_GNRC_NETIF || \
        MODULE_GNRC_UHCPC || MODULE_AUTO_INIT_GNRC_RPL || \
        MODULE_GNRC_RPL  
*/
    DYN_BOOT_GNRC,
#endif
#ifdef MODULE_PS
    DYN_BOOT_MODULE_PS,
#endif
#ifdef MODULE_SAUL
    DYN_BOOT_MODULE_SAUL,
#endif
#ifdef MODULE_PRNG
    DYN_BOOT_MODULE_PRNG,
#endif
#ifdef MODULE_PERIPH_HWRNG
    DYN_BOOT_MODULE_HWRNG,
#endif
#ifdef MODULE_PERIPH_PM
    DYN_BOOT_MODULE_PM,
#endif
#ifdef MODULE_PERIPH_UART
    DYN_BOOT_MODULE_UART,
#endif
#ifdef MODULE_RANDOM
    DYN_BOOT_MODULE_RANDOM,
#endif
#ifdef MODULE_SHELL
    DYN_BOOT_MODULE_SHELL,
#endif
#ifdef MODULE_ADXL345
    DYN_BOOT_MODULE_ADXL345,
#endif
#ifdef MODULE_BMP180
    DYN_BOOT_MODULE_BMP180,
#endif
#ifdef MODULE_L3G4200D
    DYN_BOOT_MODULE_L3G4200D,
#endif
#ifdef MODULE_XTIMER
    DYN_BOOT_MODULE_XTIMER,
#endif

    /*
     * Peripherals
     */
#ifdef MODULE_PERIPH_I2C
    DYN_BOOT_PERIPH_I2C,
#endif
#ifdef MODULE_PERIPH_SPI
    DYN_BOOT_PERIPH_SPI,
#endif
#ifdef MODULE_PERIPH_RTC
    DYN_BOOT_PERIPH_RTC,
#endif

    DYN_BOOT_MODULES_COUNT
} dyn_boot_modules_t;

int dyn_boot_get_flag(dyn_boot_modules_t module);

int auto_select_modules(void);

// void toggle_flag(void);

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_H */
/** @} */
