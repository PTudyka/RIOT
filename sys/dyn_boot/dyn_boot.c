/*
 * Copyright (C) 2020 TU-BS IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_dyn_boot
 * @{
 *
 * @file
 * @brief       Dynamic Boot Behaviour implementation
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include "dyn_boot.h"
#include "stdio.h"

/* Implementation of the module */
char MODULE_FLAGS = 0x01;

int get_flag(char bit)
{
    return (MODULE_FLAGS & (1 << bit));
}

int auto_select_modules(void)
{
    // (void) puts(MODULES_LIST);
    const char *modules = MODULES_LIST;
    (void) puts(modules);

    return -1;
}

void toggle_flag(void)
{
    // char val = MODULE_FLAGS[0];
    if (MODULE_FLAGS)
    {
        MODULE_FLAGS = 0x00;
    }
    else
    {
        MODULE_FLAGS = 0x01;
    }
}