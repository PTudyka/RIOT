/*
 * main.c
 *
 *  Created on: 02.08.2020
 *      Author: ptudyka
 */


#include <stdio.h>
#include <string.h>

#include "thread.h"

#ifdef MODULE_SHELL
#include "shell.h"
#include "shell_commands.h"
#endif

#include "net/netdev.h"
#include "net/netopt.h"

#ifdef MODULE_NETIF
#include "net/gnrc.h"
#endif
#ifdef MODULE_GNRC_PKTDUMP
#include "net/gnrc/pktdump.h"
#endif

#include "dyn_boot.h"
#include "periph/pm.h"

int toggle(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    toggle_flag();

    printf("MODULES_FLAG: %d\n", get_flag(0));

    // printf("MODULE_AUTO_INIT_GNRC_NETIF: %d\n", MODULE_AUTO_INIT_GNRC_NETIF);

    // pm_reboot();

    return 0;
}

static const shell_command_t commands[] = {
    { "toggle", "toggles modules flag", toggle },
    { NULL, NULL, NULL }
};

int main(void)
{   
#ifdef MODULE_GNRC_PKTDUMP
//    gpio_toggle(MODULES_GPIO_PIN);
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
//    gpio_toggle(MODULES_GPIO_PIN);
#endif

    // (void) auto_select_modules();

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
