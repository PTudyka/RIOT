/*
 * Copyright (C) 2020 ptudyka
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
 * @brief       Example for using AT86RF215 radio chip
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include <stdio.h>
#include "periph/i2c.h"

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"

#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"

int main(void)
{
    /* enable pktdump output */
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);

    /* start the shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
