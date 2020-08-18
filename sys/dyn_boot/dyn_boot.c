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

/* Implementation of the module */
#define MODULE_FLAGS_SIZE ((DYN_BOOT_MODULES_COUNT & 7) == 0 ? (DYN_BOOT_MODULES_COUNT >> 3) : ((DYN_BOOT_MODULES_COUNT >> 3) +1))
module_flags_t MODULE_FLAGS[MODULE_FLAGS_SIZE];

bool dyn_boot_get_flag(dyn_boot_modules_t module)
{
    /*
     * module / 8 to get array index (module >> 3)
     * module % 8 to get bit index (module & 7)
     */
    return (MODULE_FLAGS[module >> 3] & (1 << (module & 7)));
}

static inline void _dyn_boot_set_flag(dyn_boot_modules_t module, bool val)
{
    if (val)
    {
        MODULE_FLAGS[module >> 3] |= (1 << (module & 7));
    }
    else
    {
        MODULE_FLAGS[module >> 3] &= ~(1 << (module & 7));
    }
}

int auto_select_modules(void)
{
    // printf("MODULE_FLAGS size: %d\n", DYN_BOOT_MODULES_COUNT >> 3);
    printf("Modules Count: %d\n", DYN_BOOT_MODULES_COUNT);
    printf("Calculated Count: %d\n", MODULE_FLAGS_SIZE);

    // Fill with zeros at start
    unsigned i;
    for(i=0; i < MODULE_FLAGS_SIZE; ++i)
    {
        MODULE_FLAGS[i] = 0xFF;
        printf("MODULES_FLAGS: %d\n", MODULE_FLAGS[i]);
    }
    // (void) puts(MODULES_LIST);
    // const char *modules = MODULES_LIST;
    // (void) puts(modules);

    /*
     * Deactivate SAUL, if not a single sensor is activated
     */
    // bool sensor_count = (MODULE_FLAGS[0] > 0x00);
    // if (dyn_boot_get_flag)

    // _dyn_boot_set_flag(DYN_BOOT_MODULE_SAUL, sensor_count);

    return -1;
}

// void toggle_flag(void)
// {
//     // char val = MODULE_FLAGS[0];
//     if (MODULE_FLAGS)
//     {
//         MODULE_FLAGS = 0x00;
//     }
//     else
//     {
//         MODULE_FLAGS = 0x01;
//     }
// }