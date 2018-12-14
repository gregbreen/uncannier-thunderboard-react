///-----------------------------------------------------------------------------
///
/// @file em_cmu.cpp
///
/// @brief Stubs for platform/emlib/src/em_cmu.c
///
/// @copyright Copyright (c) Uncannier Software 2018
///
///-----------------------------------------------------------------------------

#include <cstdint>
#include <em_cmu.h>


void CMU_ClockEnable( CMU_Clock_TypeDef clock, bool enable )
{
}

uint32_t CMU_ClockFreqGet( CMU_Clock_TypeDef clock )
{
    return 0;
}

void CMU_ClockSelectSet( CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref )
{
}

void CMU_HFXOAutostartEnable( uint32_t userSel, bool enEM0EM1Start, bool enEM0EM1StartSel )
{
}

void CMU_HFXOInit( const CMU_HFXOInit_TypeDef *hfxoInit )
{
}

void CMU_LFXOInit( const CMU_LFXOInit_TypeDef *lfxoInit )
{
}

void CMU_OscillatorEnable( CMU_Osc_TypeDef osc, bool enable, bool wait )
{
}
