/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
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
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "thread.h"

#ifdef MODULE_SHELL
#include "shell.h"
#include "shell_commands.h"
#endif

#include "board.h"

#include "periph/pm.h"

#include "net/netdev.h"
#include "net/netopt.h"
#include "xtimer.h"

#ifdef MODULE_NETIF
#include "net/gnrc.h"
#endif
#ifdef MODULE_GNRC_PKTDUMP
#include "net/gnrc/pktdump.h"
#endif


#ifdef MODULE_TIMING_MEASUREMENT
#include "timing_measurement.h"
#endif
#ifdef MODULE_DYN_BOOT
#include "dyn_boot.h"
#endif
#include "periph_conf.h"
#include "periph/adc.h"
#define RES ADC_RES_10BIT
#define LINE 0b11110

int get_supply_voltage(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // Measure bandgap reference
    // ADMUX |= 0x01;
    // int adc_result = adc_sample(LINE, RES);

    int adc_result = 0;
    // for (unsigned int i=0; i < 3; ++i)
    // {
    //     (void) adc_sample(LINE, RES);
    // }
    adc_result = adc_sample(LINE, RES);

    printf("ADC Result: %d\n", adc_result);

    return 0;
}

int get_current_run_level(int argc, char **argv)
{
    (void) argc;
    (void) argv;

#ifdef MODULE_DYN_BOOT
    run_level_t run_level = get_run_level();
    printf("Run Level: %d\n", run_level);
#endif

#ifdef INTERN_TIMING_MEASUREMENT
    printf("INTERN_TIMING_MEASUREMENT defined\n");
#endif

#ifdef EXTERN_GPIO_MEASUREMENT
    printf("EXTERN_GPIO_MEASUREMENT defined\n");
#endif

    return 0;
}

// int get_gpios(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;

//     // gpio_init(GPIO_PIN(PORT_C, 2), GPIO_IN);
//     gpio_init(GPIO_PIN(PORT_C, 3), GPIO_IN_PD);
//     gpio_init(GPIO_PIN(PORT_C, 4), GPIO_IN_PD);
//     gpio_init(GPIO_PIN(PORT_C, 5), GPIO_IN_PD);

//     // uint8_t pc2 = gpio_read(GPIO_PIN(PORT_C, 2));
//     uint8_t pc3 = gpio_read(GPIO_PIN(PORT_C, 3));
//     uint8_t pc4 = gpio_read(GPIO_PIN(PORT_C, 4));
//     uint8_t pc5 = gpio_read(GPIO_PIN(PORT_C, 5));

//     printf("PC3: %d, PC4: %d, PC5: %d\n", pc3, pc4, pc5);

//     return 0;
// }

int get_ts(int argc, char **argv)
{
    (void) argc;
    (void) argv;

#ifdef MODULE_TIMING_MEASUREMENT
    printf("Module timing for at86rf2xx: %u us\n", get_time_for_module(MODULE_0));
    printf("Module timing for adxl345: %u us\n", get_time_for_module(MODULE_1));
    printf("Module timing for bmp180: %u us\n", get_time_for_module(MODULE_2));
    printf("Module timing for l3g4200d: %u us\n", get_time_for_module(MODULE_3));
#endif
    return 0;
}

int measure_timings(int argc, char **argv)
{
    (void) argc;
    (void) argv;

#ifdef MODULE_TIMING_MEASUREMENT

    printf("Radio send message time: %u us\n", get_time_for_module(MODULE_4));
    printf("adxl345 Read Time: %u us\n", get_time_for_module(MODULE_5));
    printf("bmp180 Read Time: %u us\n", get_time_for_module(MODULE_6));
    printf("l3g4200d Read Time: %u us\n", get_time_for_module(MODULE_7));

    reset_time_for_module(MODULE_4);
    reset_time_for_module(MODULE_5);
    reset_time_for_module(MODULE_6);
    reset_time_for_module(MODULE_7);
#endif

    return 0;
}

static const shell_command_t commands[] = {
    { "get_supply_v", "get supply voltage via ADC", get_supply_voltage },
    { "run_level", "get current run level", get_current_run_level },
    { "get_ts", "get module timing for radio init", get_ts },
    { "timings", "measure timings for radio send", measure_timings },
    // { "get_gpios", "get current gpio states for PC2,3,4,5", get_gpios },
    { NULL, NULL, NULL }
};

// void *send_thread(void *arg)
// {
//     gnrc_netif_t *ieee802154_netif = arg;

//     /// 0 Adress length means we want to use broadcast
//     size_t addr_len = 0;
//     uint8_t addr[GNRC_NETIF_L2ADDR_MAXLEN];
//     gnrc_pktsnip_t *pkt, *hdr;
//     gnrc_netif_hdr_t *nethdr;

//     /// Send packet as broadcast
//     uint8_t flags = 0 | GNRC_NETIF_HDR_FLAGS_BROADCAST;
    
//     /// payload
//     char message[] = "RIOT says hello.\0";
    
//     while(1) {
//         /// Sleep 1 second
//         xtimer_sleep(SEND_INTERVAL);

//         // Wait for a message to send
//         // Reset FLAG if a messag should be sent
//         if (!SEND_MESG_FLAG) { continue; }
//         else { SEND_MESG_FLAG = 0; }

//         // printf("MSG: %s\n", CURRENT_MSG);

//         pkt = gnrc_pktbuf_add(NULL, message, sizeof(message), GNRC_NETTYPE_UNDEF);
//         if (pkt == NULL) {
//             puts("ERROR: packet buffer full");
//             return NULL;
//         }

//         hdr = gnrc_netif_hdr_build(NULL, 0, addr, addr_len);
//         if (hdr == NULL) {
//             puts("ERROR: packet buffer full");
//             gnrc_pktbuf_release(pkt);
//             return NULL;
//         }
//         LL_PREPEND(pkt, hdr);
//         nethdr = (gnrc_netif_hdr_t *)hdr->data;
//         nethdr->flags = flags;
//         int ret = gnrc_netapi_send(ieee802154_netif->pid, pkt);
//         if (ret < 1) {
//             printf("[send_thread] unable to send: %d\n", ret);
//             gnrc_pktbuf_release(pkt);
//         } else {
//             puts("[send_thread] sent message");
//         }
//     }
//     return NULL;
// }

int main(void)
{
   gpio_toggle(MODULES_GPIO_PIN);
   
#ifdef MODULE_GNRC_PKTDUMP
//    gpio_toggle(MODULES_GPIO_PIN);
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
//    gpio_toggle(MODULES_GPIO_PIN);
#endif

    // set radio to sleep mode
//    gnrc_netif_t *netif = NULL;
//    if(!(netif = gnrc_netif_iter(netif))) {
//        puts("Unable to find netif");
//    }
//    netopt_state_t target_state = NETOPT_STATE_SLEEP;
////    printf("target_state: %d\n", target_state);
//    int ret = netif->dev->driver->set(netif->dev, NETOPT_STATE, (void *)&target_state, sizeof(netopt_state_t));
//    if (ret == -EINVAL)
//    {
//        puts("Invalid value");
//    }
//    else if (ret == -ENOTSUP)
//    {
//        puts("Opt not configurable for device");
//    }
//    else
//    {
//        printf("Bytes written: %d\n", ret);
//    }
//    while (1)
//    {
//        netopt_state_t state = NETOPT_STATE_OFF;
//        (void) netif->dev->driver->get(netif->dev, NETOPT_STATE, &state, 1);
////        printf("bytes: %d\n", bytes);
//        printf("state: %d\n", state);
//
//        xtimer_sleep(2);
//    }

    // Init send_thread for radio transmitting
    // gnrc_netif_t *netif = NULL;
    // if((netif = gnrc_netif_iter(netif))) {
    //     gnrc_netif_t *ieee802154_netif = netif;
    //     send_thread_pid = thread_create(send_thread_stack, sizeof(send_thread_stack), THREAD_PRIORITY_MAIN + 2, THREAD_CREATE_STACKTEST, send_thread, ieee802154_netif, "send_thread");
    // } else {
    //     puts("Unable to find netif");
    // }

    // Init adc line for bandgap measurement
    adc_init(LINE);

    // (void) puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];

    // gpio_toggle(STARTUP_GPIO_PIN);
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
