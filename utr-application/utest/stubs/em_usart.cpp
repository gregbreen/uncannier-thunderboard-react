///-----------------------------------------------------------------------------
///
/// @file em_usart.cpp
///
/// @brief Stubs for platform/emlib/src/em_usart.c
///
/// @copyright Copyright (c) Uncannier Software 2018
///
///-----------------------------------------------------------------------------

#include <cstdint>
#include <em_usart.h>


void USART_InitSync( USART_TypeDef *usart, const USART_InitSync_TypeDef *init )
{
}

void USART_Reset( USART_TypeDef *usart )
{
}

uint8_t USART_SpiTransfer( USART_TypeDef *usart, uint8_t data )
{
    return 0;
}
