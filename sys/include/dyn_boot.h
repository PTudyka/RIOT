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
