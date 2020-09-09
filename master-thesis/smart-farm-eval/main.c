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
 * @brief       Evaluation application in context of smart farming
 *
 * @author      ptudyka <p.tudyka@tu-bs.de>
 *
 * @}
 */

#include <stdio.h>
#include <stdbool.h>
#include "dyn_boot.h"
// #include "periph/pm.h"
#include "ringbuffer.h"
#include "net/gnrc.h"

#include "board.h"
// #include "gpio_measurement.h"

/* Sensor specific includes */
#include "bmp180.h"
#include "bmp180_params.h"
#include "phydat.h"

#include "saul_reg.h"

/* Ringbuffer specific defines */
#define RB_BUF_SIZE 16
#define DATA_SIZE (sizeof(sensor_data))

/* States of smart farming application */
typedef enum {
    NODE_GET_RUN_LEVEL,
    NODE_MEASUREMENT,
    NODE_SEND_PACKET,
    NODE_SAVE_DATA,
    NODE_SLEEP,
    NODE_ERROR
} node_status_t;
static node_status_t next_status = NODE_GET_RUN_LEVEL;

/* Ringbuffer to save leftover packets */
static char rb_buf[RB_BUF_SIZE];
static ringbuffer_t rb = RINGBUFFER_INIT(rb_buf);

/* Flag to indicate, if packets from ringbuffer should be sent */
static bool SEND_RINGBUFFER_PACKETS = false;

/* Save run_level to react on different energy conditions */
static run_level_t current_run_level = RUN_LEVEL_7;

/* Save read sensor data globally */
static uint32_t sensor_data = 0;
static phydat_t sensor_data_phy;
static char sensor_data_buf[DATA_SIZE];

static inline void pack_to_phydat(uint32_t pressure_val, phydat_t *res)
{
    res->val[0] = pressure_val / 100;
    res->unit = UNIT_PA;
    res->scale = 2;
}

void read_sensor_data(void)
{
    // Init sensor for reading
    // bmp180_t dev;
    // if(bmp180_init(&dev, &bmp180_params[0]))
    // {
    //     puts("Init bmp180 failed!");
    //     next_status = NODE_ERROR;
    //     return;
    // }
    // sensor_data = bmp180_read_pressure(&dev);

    // /* Print as phy_dat_t for debug purpose */
    // // phydat_t data;
    // pack_to_phydat(sensor_data, &sensor_data_phy);
    // phydat_dump(&sensor_data_phy, 1);

    /* Read sensor data via SAUL */
    puts("SAUL test application");
    saul_reg_t *dev = saul_reg_find_type(SAUL_SENSE_PRESS);
    if (dev == NULL) {
        puts("No SAUL Pressure Device present");
        return;
    }
    int dim = saul_reg_read(dev, &sensor_data_phy);
    // printf("\nDev: %s\tType: %s\n", dev->name,
    //         saul_class_to_str(dev->driver->type));
    phydat_dump(&sensor_data_phy, dim);

    // while (dev) {
    //     dev = dev->next;
    // }
    // puts("\n##########################");
}

void send_packet(void)
{
    // Init send_thread for radio transmitting
    gnrc_netif_t *netif = NULL;
    if(!(netif = gnrc_netif_iter(netif))) {
        puts("Unable to find netif");
        next_status = NODE_ERROR;
        return;
    }

    /// 0 Adress length means we want to use broadcast
    size_t addr_len = 0;
    uint8_t addr[GNRC_NETIF_L2ADDR_MAXLEN];
    gnrc_pktsnip_t *pkt, *hdr;
    gnrc_netif_hdr_t *nethdr;

    /// Send packet as broadcast
    uint8_t flags = 0 | GNRC_NETIF_HDR_FLAGS_BROADCAST;
    
    /// payload
    char message[sizeof(phydat_t) +1]; // Sensor_data + \0 termination char
    message[sizeof(phydat_t)] = '\0';

    printf("Size of phydat_t: %d\n", sizeof(phydat_t));
    memcpy(message, &sensor_data_phy, sizeof(phydat_t));
    printf("Message to send: %s\n", message);

    /// Build packet buffer
    pkt = gnrc_pktbuf_add(NULL, message, sizeof(message), GNRC_NETTYPE_UNDEF);
    if (pkt == NULL) {
        puts("ERROR: packet buffer full");
        return;
    }

    /// Build meassage header
    hdr = gnrc_netif_hdr_build(NULL, 0, addr, addr_len);
    if (hdr == NULL) {
        puts("ERROR: packet buffer full");
        gnrc_pktbuf_release(pkt);
        return;
    }
    LL_PREPEND(pkt, hdr);
    nethdr = (gnrc_netif_hdr_t *)hdr->data;
    nethdr->flags = flags;
    int ret = gnrc_netapi_send(netif->pid, pkt);
    if (ret < 1) {
        printf("[send_thread] unable to send: %d\n", ret);
        gnrc_pktbuf_release(pkt);
    } else {
        puts("[send_thread] sent message");
    }
}

int main(void)
{
    gpio_toggle(STARTUP_GPIO_PIN);
    // toggle_start_timing();

    puts("Generated RIOT application: 'smart-farm-eval'");
    printf("DATA_SIZE: %d\n", DATA_SIZE);

    while (1)
    {
        // Delay for debugging via serial
        xtimer_sleep(1);

        switch (next_status)
        {
        case NODE_GET_RUN_LEVEL:
            puts("Get_run_level reached");
            // Get current run_level from startup
            current_run_level = get_run_level();

            printf("Current run_level: %d\n", current_run_level);

            // Check, if sensor node has enough energy to take a measurement
            // Else go back to sleep
            if (current_run_level < RUN_LEVEL_2)
                next_status = NODE_SLEEP;
            else
                next_status = NODE_MEASUREMENT;
            break;

        case NODE_MEASUREMENT:
            puts("NODE_MEASUREMENT reached");
            // TODO: Get measurement from Sensor (Temp, ...)
            // sensor_data = 0xFF;
            read_sensor_data();

            /* Set next status */
            if (current_run_level > RUN_LEVEL_5)
                next_status = NODE_SEND_PACKET;
            else
                next_status = NODE_SAVE_DATA;
            break;

        case NODE_SEND_PACKET:
            puts("NODE_SEND_PACKET reached");
            // Send packet
            send_packet();

            // If current data != NULL, send this
            // Else check for SEND_MORE_DATA flag and check ringbuffer
            if (SEND_RINGBUFFER_PACKETS)
                (void) SEND_RINGBUFFER_PACKETS;

            next_status = NODE_SLEEP;
            break;

        case NODE_SAVE_DATA:
            puts("NODE_SAVE_DATA reached");
            // Save Data to ringbuffer
            // Override oldest data, if bufer is full

            /* Parse sensor data into byte array for ringbuffer packing */
            for (unsigned int i=0; i < DATA_SIZE; ++i)
            {
                sensor_data_buf[i] = (char) ((sensor_data << (i)) & 0xFF);
                // sensor_data_buf[i] = (char)(((i * 8) >> sensor_data) & 0xFF);
            }
            ringbuffer_add(&rb, sensor_data_buf, DATA_SIZE);

            printf("Ringbuffer free space: %d\n", ringbuffer_get_free(&rb));

            next_status = NODE_SLEEP;
            break;

        case NODE_SLEEP:
            puts("NODE_SLEEP reached");
            // Set to sleep (lowest possibly power mode)
            // pm_set_lowest();
            xtimer_sleep(5);

            next_status = NODE_GET_RUN_LEVEL;
            break;

        case NODE_ERROR:
            /* ERROR HANDLING */
            puts("Error State reached!");
            break;
        } /* switch (next_status) */
    } /* while (1) */

    return 0;
}
