/***************************************************************************//**
 * @file
 * @brief I2C simple poll-based master mode driver
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef __SILICON_LABS_I2CSPM_H__
#define __SILICON_LABS_I2CSPM_H__

#include "i2cspmconfig.h"
#include "em_gpio.h"
#include "em_i2c.h"

/***************************************************************************//**
 * @addtogroup I2CSPM
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 ********************************   STRUCTS   **********************************
 ******************************************************************************/

/** I2C driver instance initialization structure.
    This data structure contains a number of I2C configuration options
    required for driver instance initialization.
    This struct is passed to @ref I2CSPM_Init() when initializing a I2CSPM
    instance. */
typedef struct {
  I2C_TypeDef           *port;          /**< Peripheral port */
  GPIO_Port_TypeDef     sclPort;        /**< SCL pin port number */
  uint8_t               sclPin;         /**< SCL pin number */
  GPIO_Port_TypeDef     sdaPort;        /**< SDA pin port number */
  uint8_t               sdaPin;         /**< SDA pin number */
#if defined (_I2C_ROUTELOC0_MASK)
  uint8_t               portLocationScl; /**< Port location of SCL signal */
  uint8_t               portLocationSda; /**< Port location of SDA signal */
#else
  uint8_t               portLocation;   /**< Port location */
#endif
  uint32_t              i2cRefFreq;     /**< I2C reference clock */
  uint32_t              i2cMaxFreq;     /**< I2C max bus frequency to use */
  I2C_ClockHLR_TypeDef  i2cClhr;        /**< Clock low/high ratio control */
} I2CSPM_Init_TypeDef;

/** Default config for I2C init structure. The default may be overridden
    by a i2cspmconfig.h file. */
#if !defined(I2CSPM_INIT_DEFAULT)
#define I2CSPM_INIT_DEFAULT                                                    \
  { I2C0,                       /* Use I2C instance 0 */                       \
    gpioPortC,                  /* SCL port */                                 \
    5,                          /* SCL pin */                                  \
    gpioPortC,                  /* SDA port */                                 \
    4,                          /* SDA pin */                                  \
    0,                          /* Location */                                 \
    0,                          /* Use currently configured reference clock */ \
    I2C_FREQ_STANDARD_MAX,      /* Set to standard rate  */                    \
    i2cClockHLRStandard,        /* Set to use 4:4 low/high duty cycle */       \
  }
#endif

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void I2CSPM_Init(I2CSPM_Init_TypeDef *init);
I2C_TransferReturn_TypeDef I2CSPM_Transfer(I2C_TypeDef *i2c, I2C_TransferSeq_TypeDef *seq);

#ifdef __cplusplus
}
#endif

/** @} (end group I2CSPM) */

#endif /* __SILICON_LABS_I2CSPM_H__ */
