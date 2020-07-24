/*
 * Copyright (C) 2016 Eistec AB
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup   drivers_lis3dsh
 * @{
 *
 * @file
 * @brief     LIS3DH adaption to the RIOT actuator/sensor interface
 *
 * @author    Joakim Nohlgård <joakim.nohlgard@eistec.se>
 *
 * @}
 */

#include <string.h>
#include <stdio.h>

#include "saul.h"
#include "lis3dsh.h"

static int read_acc(const void *dev, phydat_t *res)
{
    lis3dsh_data_t xyz;

    int err = lis3dsh_read_xyz((const lis3dsh_t *)dev, &xyz);
    if (err != 0) {
        /* Something went wrong in the LIS3DSH driver */
        return -ECANCELED;
    }

    res->val[0] = xyz.acc_x;
    res->val[1] = xyz.acc_y;
    res->val[2] = xyz.acc_z;
    /* unit: milli-G */
    res->scale = -3;
    res->unit = UNIT_G;

    return 3;
}

const saul_driver_t lis3dsh_saul_driver = {
    .read = read_acc,
    .write = saul_notsup,
    .type = SAUL_SENSE_ACCEL,
};
