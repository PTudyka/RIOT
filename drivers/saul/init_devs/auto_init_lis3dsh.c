/*
 * Copyright (C) 2016 Eistec AB
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @ingroup     sys_auto_init_saul
 * @{
 *
 * @file
 * @brief       Auto initialization of LIS3DSH accelerometers
 *
 * @author      Joakim Nohlgård <joakim.nohlgard@eistec.se>
 *
 * @}
 */

#include "assert.h"
#include "log.h"
#include "saul_reg.h"
#include "lis3dsh.h"
#include "lis3dsh_params.h"

/**
 * @brief   Define the number of configured sensors
 */
#define LIS3DSH_NUM    ARRAY_SIZE(lis3dsh_params)

/**
 * @brief   Allocate memory for the device descriptors
 */
static lis3dsh_t lis3dsh_devs[LIS3DSH_NUM];

/**
 * @brief   Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[LIS3DSH_NUM];

/**
 * @brief   Define the number of saul info
 */
#define LIS3DSH_INFO_NUM    ARRAY_SIZE(lis3dsh_saul_info)

/**
 * @brief   Reference the driver struct
 */
extern saul_driver_t lis3dsh_saul_driver;


void auto_init_lis3dsh(void)
{
    assert(LIS3DSH_NUM == LIS3DSH_INFO_NUM);

    for (unsigned int i = 0; i < LIS3DSH_NUM; i++) {
        LOG_DEBUG("[auto_init_saul] initializing lis3dsh #%u\n", i);

        if (lis3dsh_init(&lis3dsh_devs[i], &lis3dsh_params[i]) < 0) {
            LOG_ERROR("[auto_init_saul] error initializing lis3dsh #%u\n", i);
            continue;
        }

        if (lis3dsh_set_odr(&lis3dsh_devs[i], lis3dsh_params[i].odr) < 0) {
            LOG_ERROR("[auto_init_saul] error setting ODR for lis3dsh #%u\n", i);
            continue;
        }

        saul_entries[i].dev = &(lis3dsh_devs[i]);
        saul_entries[i].name = lis3dsh_saul_info[i].name;
        saul_entries[i].driver = &lis3dsh_saul_driver;
        saul_reg_add(&(saul_entries[i]));
    }
}
