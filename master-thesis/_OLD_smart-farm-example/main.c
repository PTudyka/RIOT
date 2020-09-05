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
#include "xtimer.h"

#ifdef MODULE_TIMING_MEASUREMENT
#include "timing_measurement.h"
#endif

int toggle(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // toggle_flag();

    printf("MODULES_FLAG: %d\n", dyn_boot_get_flag(DYN_BOOT_MODULE_SAUL));

    // pm_reboot();

    return 0;
}

// int get_modules(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;

//     unsigned int i=0;
//     // char time_buffer[TIMEX_MAX_STR_LEN];
//     for (i=0; i < MODULE_TIMINGS_SIZE; ++i)
//     {
//         // (void) timex_to_str(get_time_for_module(i), time_buffer);
//         printf("Module: %d -> Time: %u\n", i, get_time_for_module(i));
//     }

//     return 0;
// }

int get_timestamp(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    uint32_t timestamp = xtimer_now_usec();
    printf("Current timestamp: %u\n", timestamp);

    return 0;
}

static const shell_command_t commands[] = {
    { "toggle", "toggles modules flag", toggle },
    // { "get_modules", "get timings for all modules", get_modules },
    { "get_ts", "Prints current timestamp 64", get_timestamp },
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
