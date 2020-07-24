/*
 * Copyright (C) 2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_lis3dsh
 *
 * @{
 * @file
 * @brief       Default configuration for LIS3DSH devices
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef LIS3DSH_PARAMS_H
#define LIS3DSH_PARAMS_H

#include "board.h"
#include "lis3dsh.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters
 * @{
 */
#ifndef LIS3DSH_PARAM_SPI
#define LIS3DSH_PARAM_SPI            (SPI_DEV(0))
#endif
#ifndef LIS3DSH_PARAM_CS
// #define LIS3DSH_PARAM_CS             (GPIO_PIN(PORT_B, 12))
#define LIS3DSH_PARAM_CS             (GPIO_PIN(PORT_E, 3))
#endif
#ifndef LIS3DSH_PARAM_CLK
#define LIS3DSH_PARAM_CLK            (SPI_CLK_5MHZ)
#endif
#ifndef LIS3DSH_PARAM_INT1
#define LIS3DSH_PARAM_INT1           (GPIO_PIN(PORT_E, 0))
#endif
#ifndef LIS3DSH_PARAM_INT2
#define LIS3DSH_PARAM_INT2           (GPIO_PIN(PORT_E, 1))
#endif
#ifndef LIS3DSH_PARAM_SCALE
#define LIS3DSH_PARAM_SCALE          (2)
#endif
#ifndef LIS3DSH_PARAM_ODR
#define LIS3DSH_PARAM_ODR            (LIS3DSH_ODR_100Hz)
#endif

#ifndef LIS3DSH_PARAMS
#define LIS3DSH_PARAMS               { .spi   = LIS3DSH_PARAM_SPI,   \
                                      .cs    = LIS3DSH_PARAM_CS,    \
                                      .clk   = LIS3DSH_PARAM_CLK,   \
                                      .int1  = LIS3DSH_PARAM_INT1,  \
                                      .int2  = LIS3DSH_PARAM_INT2,  \
                                      .scale = LIS3DSH_PARAM_SCALE, \
                                      .odr   = LIS3DSH_PARAM_ODR }
#endif
#ifndef LIS3DSH_SAUL_INFO
#define LIS3DSH_SAUL_INFO            { .name = "lis3dsh" }
#endif
/**@}*/

/**
 * @brief   Allocate some memory to store the actual configuration
 */
static const lis3dsh_params_t lis3dsh_params[] =
{
    LIS3DSH_PARAMS
};

/**
 * @brief   Additional meta information to keep in the SAUL registry
 */
static const saul_reg_info_t lis3dsh_saul_info[] =
{
    LIS3DSH_SAUL_INFO
};

#ifdef __cplusplus
}
#endif

#endif /* LIS3DSH_PARAMS_H */
/** @} */
