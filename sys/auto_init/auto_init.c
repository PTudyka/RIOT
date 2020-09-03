/**
 * Auto initialization for used modules
 *
 * Copyright (C) 2020 Freie Universität Berlin
 *               2020 Kaspar Schleiser <kaspar@schleiser.de>
 *               2013  INRIA.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 * @ingroup sys_auto_init
 * @{
 * @file
 * @brief   initializes any used module that has a trivial init function
 * @author  Oliver Hahm <oliver.hahm@inria.fr>
 * @author  Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author  Kaspar Schleiser <kaspar@schleiser.de>
 * @author  Martine S. Lenders <m.lenders@fu-berlin.de>
 * @}
 */
#include <stdint.h>
#include <stdio.h>

#include "auto_init.h"
#include "kernel_defines.h"
#include "log.h"

#include "board.h"
// #include "dyn_boot.h"

void auto_init(void)
{
    // auto_select_modules();

    if (IS_USED(MODULE_AUTO_INIT_RANDOM)) {
        LOG_DEBUG("Auto init random.\n");
        extern void auto_init_random(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_random();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    // else
    // {
    //     /* Still toggle GPIO Pin, to make analysis easier later */
    //     gpio_toggle(MODULES_GPIO_PIN);
    //     gpio_toggle(MODULES_GPIO_PIN);
    // }
    
    if (IS_USED(MODULE_AUTO_INIT_ZTIMER)) {
        LOG_DEBUG("Auto init ztimer.\n");
        void ztimer_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        ztimer_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_XTIMER) &&
            !IS_USED(MODULE_ZTIMER_XTIMER_COMPAT)) {
        LOG_DEBUG("Auto init xtimer.\n");
        extern void xtimer_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        xtimer_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_SCHEDSTATISTICS)) {
        LOG_DEBUG("Auto init schedstatistics.\n");
        extern void init_schedstatistics(void);
        gpio_toggle(MODULES_GPIO_PIN);
        init_schedstatistics();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_DUMMY_THREAD)) {
        extern void dummy_thread_create(void);
        gpio_toggle(MODULES_GPIO_PIN);
        dummy_thread_create();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_EVENT_THREAD)) {
        LOG_DEBUG("Auto init event threads.\n");
        extern void auto_init_event_thread(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_event_thread();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_MCI)) {
        LOG_DEBUG("Auto init mci.\n");
        extern void mci_initialize(void);
        gpio_toggle(MODULES_GPIO_PIN);
        mci_initialize();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_PROFILING)) {
        LOG_DEBUG("Auto init profiling.\n");
        extern void profiling_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        profiling_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_PKTBUF)) {
        LOG_DEBUG("Auto init gnrc_pktbuf.\n");
        extern void gnrc_pktbuf_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_pktbuf_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_PKTDUMP)) {
        LOG_DEBUG("Auto init gnrc_pktdump.\n");
        extern void gnrc_pktdump_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_pktdump_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_SIXLOWPAN)) {
        LOG_DEBUG("Auto init gnrc_sixlowpan.\n");
        extern void gnrc_sixlowpan_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_sixlowpan_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_IPV6)) {
        LOG_DEBUG("Auto init gnrc_ipv6.\n");
        extern void gnrc_ipv6_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_ipv6_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_UDP)) {
        LOG_DEBUG("Auto init gnrc_udp.\n");
        extern void gnrc_udp_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_udp_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_TCP)) {
        LOG_DEBUG("Auto init gnrc_tcp.\n");
        extern void gnrc_tcp_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_tcp_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_LWIP)) {
        LOG_DEBUG("Bootstraping lwIP.\n");
        extern void lwip_bootstrap(void);
        gpio_toggle(MODULES_GPIO_PIN);
        lwip_bootstrap();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_OPENTHREAD)) {
        LOG_DEBUG("Bootstrapping openthread.\n");
        extern void openthread_bootstrap(void);
        gpio_toggle(MODULES_GPIO_PIN);
        openthread_bootstrap();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_OPENWSN)) {
        LOG_DEBUG("Bootstrapping openwsn.\n");
        extern void openwsn_bootstrap(void);
        openwsn_bootstrap();
    }
    if (IS_USED(MODULE_GCOAP) &&
        !IS_ACTIVE(CONFIG_GCOAP_NO_AUTO_INIT)) {
        LOG_DEBUG("Auto init gcoap.\n");
        extern void gcoap_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gcoap_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_DEVFS)) {
        LOG_DEBUG("Mounting /dev.\n");
        extern void auto_init_devfs(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_devfs();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_GNRC_IPV6_NIB)) {
        LOG_DEBUG("Auto init gnrc_ipv6_nib.\n");
        extern void gnrc_ipv6_nib_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_ipv6_nib_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_SKALD)) {
        LOG_DEBUG("Auto init Skald.\n");
        extern void skald_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        skald_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_CORD_COMMON)) {
        LOG_DEBUG("Auto init cord_common.\n");
        extern void cord_common_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        cord_common_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_CORD_EP_STANDALONE)) {
        LOG_DEBUG("Auto init cord_ep_standalone.\n");
        extern void cord_ep_standalone_run(void);
        gpio_toggle(MODULES_GPIO_PIN);
        cord_ep_standalone_run();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_ASYMCUTE)) {
        LOG_DEBUG("Auto init Asymcute.\n");
        extern void asymcute_handler_run(void);
        gpio_toggle(MODULES_GPIO_PIN);
        asymcute_handler_run();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_NIMBLE)) {
        LOG_DEBUG("Auto init NimBLE.\n");
        extern void nimble_riot_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        nimble_riot_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_AUTO_INIT_LORAMAC)) {
        LOG_DEBUG("Auto init loramac.\n");
        extern void auto_init_loramac(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_loramac();
        gpio_toggle(MODULES_GPIO_PIN);
    }
    if (IS_USED(MODULE_SOCK_DTLS)) {
        LOG_DEBUG("Auto init sock_dtls.\n");
        extern void sock_dtls_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        sock_dtls_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    /* initialize USB devices */
    if (IS_USED(MODULE_AUTO_INIT_USBUS)) {
        LOG_DEBUG("Auto init USB.\n");
        extern void auto_init_usb(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_usb();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    /* initialize network devices */
    if (IS_USED(MODULE_AUTO_INIT_GNRC_NETIF)) {
        LOG_DEBUG("Auto init gnrc_netif.\n");
        extern void gnrc_netif_init_devs(void);
        // gpio_toggle(MODULES_GPIO_PIN);
        // if(get_flag(0)) gnrc_netif_init_devs();
        gnrc_netif_init_devs();
        // gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_GNRC_UHCPC)) {
        LOG_DEBUG("Auto init gnrc_uhcpc.\n");
        extern void auto_init_gnrc_uhcpc(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_gnrc_uhcpc();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    /* initialize NDN module after the network devices are initialized */
    if (IS_USED(MODULE_NDN_RIOT)) {
        LOG_DEBUG("Auto init NDN.\n");
        extern void ndn_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        ndn_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    /* initialize sensors and actuators */
    if (IS_USED(MODULE_SHT1X)) {
        /* The sht1x module needs to be initialized regardless of SAUL being used,
         * as the shell commands rely on auto-initialization. auto_init_sht1x also
         * performs SAUL registration, but only if module auto_init_saul is used.
         */
        LOG_DEBUG("Auto init sht1x.\n");
        extern void auto_init_sht1x(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_sht1x();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_SAUL)) {
        LOG_DEBUG("Auto init SAUL.\n");
        extern void saul_init_devs(void);
        // gpio_toggle(MODULES_GPIO_PIN);
        saul_init_devs();
        // gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_GNRC_RPL)) {
        LOG_DEBUG("Auto init gnrc_rpl.\n");
        extern void auto_init_gnrc_rpl(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_gnrc_rpl();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_CAN)) {
        LOG_DEBUG("Auto init CAN.\n");

        extern void auto_init_candev(void);
        gpio_toggle(MODULES_GPIO_PIN);
        auto_init_candev();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_SUIT)) {
        LOG_DEBUG("Auto init SUIT conditions.\n");
        extern void suit_init_conditions(void);
        gpio_toggle(MODULES_GPIO_PIN);
        suit_init_conditions();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_SECURITY)) {
        if (IS_USED(MODULE_CRYPTOAUTHLIB)) {
            LOG_DEBUG("Auto init cryptoauthlib.\n");
            extern void auto_init_atca(void);
            gpio_toggle(MODULES_GPIO_PIN);
            auto_init_atca();
            gpio_toggle(MODULES_GPIO_PIN);
        }
    }

    if (IS_USED(MODULE_TEST_UTILS_INTERACTIVE_SYNC) && !IS_USED(MODULE_SHELL)) {
        extern void test_utils_interactive_sync(void);
        gpio_toggle(MODULES_GPIO_PIN);
        test_utils_interactive_sync();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_DHCPV6_CLIENT)) {
        LOG_DEBUG("Auto init DHCPv6 client.\n");
        extern void dhcpv6_client_auto_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        dhcpv6_client_auto_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_GNRC_DHCPV6_CLIENT_6LBR)) {
        LOG_DEBUG("Auto init 6LoWPAN border router DHCPv6 client\n");
        extern void gnrc_dhcpv6_client_6lbr_init(void);
        gpio_toggle(MODULES_GPIO_PIN);
        gnrc_dhcpv6_client_6lbr_init();
        gpio_toggle(MODULES_GPIO_PIN);
    }

    if (IS_USED(MODULE_AUTO_INIT_MULTIMEDIA)) {
        LOG_DEBUG("auto_init MULTIMEDIA\n");
        if (IS_USED(MODULE_DFPLAYER)) {
            extern void auto_init_dfplayer(void);
            auto_init_dfplayer();
        }
    }
}
