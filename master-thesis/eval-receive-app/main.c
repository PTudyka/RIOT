/*
 * Copyright (C) 2020 TU-BS IBR
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
 * @brief       Receiver for the sent packages of the smart-eval-application
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include <stdio.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include "xtimer.h"
#include "net/gnrc.h"
#include "net/gnrc/netreg.h"
#include "net/gnrc/netif/ieee802154.h"

#include "phydat.h"

#define RCV_QUEUE_SIZE (16)

char dump_thread_stack[512+256];

// static inline void parse_stm32f4_phydat(phydat_t *data)
// {
//     // 3 items offset in enum, compared to inga phydat enum
//     data->unit = data->unit +3;
// }

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
                (void) hdr;
                // /// Print payload
                phydat_t phydat;
                memcpy(&phydat, (char*)payload->data, sizeof(phydat_t));
                // parse_stm32f4_phydat(&phydat);
                // printf("phydat: val[0]: %d, unit: %d, scale: %d\n", phydat.val[0], phydat.unit, phydat.scale);
                phydat_dump(&phydat, 1);

                // printf("phydat_t size: %d\n", sizeof(phydat_t));
                // printf("Received: %x %x %x %x %x %x %x %x\n", ((char*) payload->data)[0], ((char*) payload->data)[1], 
                // ((char*) payload->data)[2], ((char*) payload->data)[3], ((char*) payload->data)[4], 
                // ((char*) payload->data)[5], ((char*) payload->data)[6], ((char*) payload->data)[7]);
                // printf("Received message: '%s'\n", (char*)payload->data);
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

int main(void)
{
    puts("Generated RIOT application: 'eval-receive-app'");

    thread_create(dump_thread_stack, sizeof(dump_thread_stack), THREAD_PRIORITY_MAIN + 1, THREAD_CREATE_STACKTEST, dump_thread, NULL, "dump_thread");

    return 0;
}
