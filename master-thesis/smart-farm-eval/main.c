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

// #include <stdio.h>
#include <stdbool.h>
#include "dyn_boot.h"
// #include "periph/pm.h"
#include "ringbuffer.h"
#include "net/gnrc.h"

#define RB_BUF_SIZE 16
#define DATA_SIZE (sizeof(sensor_data))

/* States of smart farming application */
typedef enum {
    NODE_MEASUREMENT,
    NODE_SEND_PACKET,
    NODE_SAVE_DATA,
    NODE_SLEEP
} node_status_t;
static node_status_t next_status = NODE_MEASUREMENT;

/* Ringbuffer to save leftover packets */
static char rb_buf[RB_BUF_SIZE];
static ringbuffer_t rb = RINGBUFFER_INIT(rb_buf);

/* Flag to indicate, if packets from ringbuffer should be sent */
static bool SEND_RINGBUFFER_PACKETS = false;

/* Save run_level to react on different energy conditions */
static run_level_t current_run_level = RUN_LEVEL_7;

/* Save read sensor data globally */
static int sensor_data = 0;
static char sensor_data_buf[DATA_SIZE];

int main(void)
{
    puts("Generated RIOT application: 'smart-farm-eval'");

    while (1)
    {
        // Get current run_level from startup
        current_run_level = get_run_level();

        // Check, if sensor node has enough energy to take a measurement
        // Else go back to sleep
        if (current_run_level < RUN_LEVEL_2)
            next_status = NODE_SLEEP;
        else
            next_status = NODE_MEASUREMENT;
        
        switch (next_status)
        {
        case NODE_MEASUREMENT:
            // TODO: Get measurement from Sensor (Temp, ...)
            sensor_data = 0xFF;
            break;

        case NODE_SEND_PACKET:
            // Send packet

            // If current data != NULL, send this
            // Else check for SEND_MORE_DATA flag and check ringbuffer
            if (SEND_RINGBUFFER_PACKETS)
                (void) SEND_RINGBUFFER_PACKETS;
            break;

        case NODE_SAVE_DATA:
            // Save Data to ringbuffer
            for (unsigned int i=0; i < DATA_SIZE; ++i)
            {
                sensor_data_buf[i] = (char)(((i * 8) >> sensor_data) & 0xFF);
            }
            ringbuffer_add(&rb, sensor_data_buf, DATA_SIZE);
            break;

        case NODE_SLEEP:
            // Set to sleep (lowest possibly power mode)
            // pm_set_lowest();
            break;
        } /* switch (next_status) */
    } /* while (1) */

    return 0;
}
