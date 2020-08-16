/*
 * Copyright (C) 2013  INRIA.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     sys_shell_commands
 * @{
 *
 * @file
 * @brief       Shell commands for the PS module
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include "ps.h"
#include "dyn_boot.h"

int _ps_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    if(!(dyn_boot_get_flag(DYN_BOOT_MODULE_PS)))
    {
        return 0;
    }

    ps();

    return 0;
}
