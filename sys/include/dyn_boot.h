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
#ifndef MODULES_LIST
#define MODULES_LIST "NO MODULES"
// #else
// #define MODULES_LIST "YES MODULES"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char flags;
} module_flags_t;

// module_flags_t module_flags = {0x00};
extern volatile module_flags_t module_flags;

// char MODULE_FLAGS = 0x00;
// Redefine Flags to auto-init flags
#ifdef MODULE_AUTO_INIT_GNRC_NETIF
#undef MODULE_AUTO_INIT_GNRC_NETIF
// #define MODULE_AUTO_INIT_GNRC_NETIF module_flags.flags & 0x01
#define MODULE_AUTO_INIT_GNRC_NETIF get_flag(0)
#endif

/* Declare the API of the module */
// char MODULE_FLAGS[] = {0x00};

int get_flag(char byte);

int auto_select_modules(void);

void toggle_flag(void);

#ifdef __cplusplus
}
#endif

#endif /* DYN_BOOT_H */
/** @} */
