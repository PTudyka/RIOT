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
static char sensor_data_buf[DATA_SIZE];


static inline void pack_to_phydat(uint32_t pressue_val, phydat_t *res)
{
    res->val[0] = pressue_val / 100;
    res->unit = UNIT_PA;
    res->scale = 2;
}

void read_sensor_data(void)
{
    // Init sensor for reading
    bmp180_t dev;
    if(bmp180_init(&dev, &bmp180_params[0]))
    {
        puts("Init bmp180 failed!");
        next_status = NODE_ERROR;
        return;
    }
    sensor_data = bmp180_read_pressure(&dev);

    /* Print as phy_dat_t for debug purpose */
    phydat_t data;
    pack_to_phydat(sensor_data, &data);
    phydat_dump(&data, 1);
}

void send_packet(void)
{
    printf("Sensor data: %u\n", sensor_data);
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
                sensor_data_buf[i] = (char)(((i * 8) >> sensor_data) & 0xFF);
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
