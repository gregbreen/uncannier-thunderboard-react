///-----------------------------------------------------------------------------
///
/// @file em_i2c.cpp
///
/// @brief Stubs for platform/emlib/src/em_i2c.c
///
/// @copyright Copyright (c) Uncannier Software 2018
///
///-----------------------------------------------------------------------------

#include <cstdint>
#include <em_i2c.h>


void I2C_Init( I2C_TypeDef *i2c, const I2C_Init_TypeDef *init )
{
}

I2C_TransferReturn_TypeDef I2C_Transfer( I2C_TypeDef *i2c )
{
    return i2cTransferDone;
}

I2C_TransferReturn_TypeDef I2C_TransferInit( I2C_TypeDef *i2c, I2C_TransferSeq_TypeDef *seq )
{
    return i2cTransferInProgress;
}

