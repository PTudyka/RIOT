/*
 * Copyright (C) 2020 IBR
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief       Tests sending and receiving broadcasts via IEEE802.15.4
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include <stdio.h>
// #include <string.h>

// #include "msg.h"
#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include "xtimer.h"
#include "net/gnrc.h"
#include "net/gnrc/netreg.h"
#include "net/gnrc/netif/ieee802154.h"

#include "net/gnrc/pktdump.h"

#include "board.h"

// Override AT86RF215 params to work with stm32f4discovery board spi
// #define AT86RF215_PARAM_SPI         (SPI_DEV(0))
// #define AT86RF215_PARAM_SPI_CLK     (SPI_CLK_5MHZ)
// #define AT86RF215_PARAM_CS          (GPIO_PIN(PORT_A, 4)) // Stm32f4discovery
// #define AT86RF215_PARAM_INT         (GPIO_PIN(PORT_E, 2))
// #define AT86RF215_PARAM_RESET       (GPIO_PIN(PORT_E, 3))

#define SEND_INTERVAL (1)
#define RCV_QUEUE_SIZE (16)

// char dump_thread_stack[512+256];
// char send_thread_stack[512+216];
char dump_thread_stack[THREAD_STACKSIZE_MAIN];
char send_thread_stack[THREAD_STACKSIZE_MAIN];

kernel_pid_t send_thread_pid = 0;

int SEND_MESG_FLAG = 0;
// char *CURRENT_MSG = NULL;
char CURRENT_MSG[256];
int CURRENT_MSG_SIZE = 0;
uint8_t *SOURCE_ADDR = NULL;
uint8_t SOURCE_ADDR_LEN = 0;

static void _dump(gnrc_pktsnip_t *pkt) {
    /// Iterate though snippets (Linked List)
    gnrc_pktsnip_t *snip = pkt;
    /// Payload and header not known
    gnrc_pktsnip_t *payload = NULL;
    gnrc_netif_hdr_t *hdr = NULL;
    
    while(snip != NULL) {
        switch(snip->type)  {
            case GNRC_NETTYPE_UNDEF :
                /// No specific network type -> payload
                payload = snip;
            break;
            case GNRC_NETTYPE_NETIF :
                /// Interface data -> header
                hdr = snip->data;
                // (void) hdr;
                /// Print payload
                printf("Received message: '%s'\n", (char*)payload->data);

                // Set message to echo it
                CURRENT_MSG_SIZE = payload->size +1;
                snprintf(CURRENT_MSG, CURRENT_MSG_SIZE, "%s", (char*)payload->data);
                // CURRENT_MSG = (char*)payload->data;
                printf("payload size: '%d'\n", CURRENT_MSG_SIZE);
                printf("payload: ");
                int i=0;
                for(i=0; i < CURRENT_MSG_SIZE; ++i)
                {
                    printf("%c", CURRENT_MSG[i]);
                }
                printf("\n");
                SOURCE_ADDR_LEN = hdr->src_l2addr_len;
                SOURCE_ADDR = gnrc_netif_hdr_get_src_addr(hdr);
                printf("header length: '%d'\n", SOURCE_ADDR_LEN);
                printf("Source addr: ");
                for(i=0; i < SOURCE_ADDR_LEN; ++i)
                {
                    printf("%x", SOURCE_ADDR[i]);
                }
                printf("\n");
                SEND_MESG_FLAG = 1;
                // thread_wakeup(send_thread_pid); // wake send_thread to send message
            break;
            default : 

            break;
        }
        snip = snip->next;
    }
    gnrc_pktbuf_release(pkt);
}

void *dump_thread(void *arg)
{
    (void) arg;
    msg_t dump_thread_msg_queue[RCV_QUEUE_SIZE];
    msg_init_queue(dump_thread_msg_queue, RCV_QUEUE_SIZE);

    gnrc_netreg_entry_t me_reg = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL, sched_active_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &me_reg);

    msg_t msg;
    while(1) {
        if(msg_receive(&msg) != 1) {
            puts("Unable to receive message");
            continue;
        }
        printf("[dump_thread] message received: %d\n", msg.type);
        switch(msg.type) {
            case GNRC_NETAPI_MSG_TYPE_RCV :
                _dump( msg.content.ptr );
            break;
        }
    }
    puts("END OF dump_thread");
    return NULL;
}

void *send_thread(void *arg)
{
    gnrc_netif_t *ieee802154_netif = arg;

    /// 0 Adress length means we want to use broadcast
    // size_t addr_len = 0;
    // size_t addr_len = SOURCE_ADDR_LEN;
    // uint8_t addr[GNRC_NETIF_L2ADDR_MAXLEN];
    // uint8_t *addr = SOURCE_ADDR;
    gnrc_pktsnip_t *pkt, *hdr;
    gnrc_netif_hdr_t *nethdr;

    /// Send packet as broadcast
    uint8_t flags = 0; // | GNRC_NETIF_HDR_FLAGS_BROADCAST;
    
    /// payload
    // char message[] = "RIOT says hello.\0";
    
    while(1) {
        /// Sleep 1 second
        while (!SEND_MESG_FLAG)
        {
            xtimer_sleep(SEND_INTERVAL);
        }
        SEND_MESG_FLAG = 0;
        
        pkt = gnrc_pktbuf_add(NULL, CURRENT_MSG, CURRENT_MSG_SIZE, GNRC_NETTYPE_UNDEF);
        if (pkt == NULL) {
            puts("ERROR: packet buffer full");
            return NULL;
        }

        // hdr = gnrc_netif_hdr_build(NULL, 0, addr, addr_len);
        hdr = gnrc_netif_hdr_build(ieee802154_netif->l2addr, ieee802154_netif->l2addr_len, SOURCE_ADDR, SOURCE_ADDR_LEN);
        if (hdr == NULL) {
            puts("ERROR: packet buffer full");
            gnrc_pktbuf_release(pkt);
            return NULL;
        }
        LL_PREPEND(pkt, hdr);
        nethdr = (gnrc_netif_hdr_t *)hdr->data;
        nethdr->flags = flags;
        int ret = gnrc_netapi_send(ieee802154_netif->pid, pkt);
        if (ret < 1) {
            printf("[send_thread] unable to send: %d\n", ret);
            gnrc_pktbuf_release(pkt);
        } else {
            puts("[send_thread] sent message");
            // gnrc_pktbuf_release(pkt);
        }
    }
    return NULL;
}

int main(void)
{
    thread_create(dump_thread_stack, sizeof(dump_thread_stack), THREAD_PRIORITY_MAIN + 1, THREAD_CREATE_STACKTEST, dump_thread, NULL, "dump_thread");
    
    /*
     * Init send_thread with networkinterface 6
     * Iface 5 doesn't work (subGhz?)
     */
    gnrc_netif_t *netif = gnrc_netif_iter(NULL);
    if (netif != NULL && netif->pid != 6) {
        netif = gnrc_netif_iter(netif);
    }
    // Create thread for first radio
    if((netif != NULL)) {
        gnrc_netif_t *ieee802154_netif = netif;
        send_thread_pid = thread_create(send_thread_stack, 
                                        sizeof(send_thread_stack), 
                                        // THREAD_PRIORITY_MAIN + 2, 
                                        THREAD_PRIORITY_MAIN -1,
                                        THREAD_CREATE_STACKTEST, 
                                        send_thread, 
                                        ieee802154_netif, 
                                        "send_thread");
    } else {
        puts("Unable to find netif");
    }

    // Create Thread for second radio
    // if((netif = gnrc_netif_iter(netif))) {
    //     gnrc_netif_t *ieee802154_netif = netif;
    //     send_thread_pid = thread_create(send_thread_stack, 
    //                                     sizeof(send_thread_stack), 
    //                                     THREAD_PRIORITY_MAIN + 2, 
    //                                     THREAD_CREATE_STACKTEST, 
    //                                     send_thread, 
    //                                     ieee802154_netif, 
    //                                     "send_thread");
    // } else {
    //     puts("Unable to find netif");
    // }

    (void) puts("Welcome to RIOT!\n");
    // (void) printf("interfaces:%d\n", gnrc_netif_numof());

    /* initialize and register pktdump to print received packets */
    // gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
    //                              gnrc_pktdump_pid);
    // gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);

    // Initialize Shell
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
