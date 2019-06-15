/***************************************************************************//**
 * @file
 * @brief Battery Device
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

#include "battery_device.h"
#include "app_timer.h"
#include "native_gecko.h"
/* emlib */
#include "em_cmu.h"
#include "em_emu.h"
#include "em_adc.h"
#include "cr2032.h"

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup battery-hw
 * @{
 **************************************************************************************************/

/***************************************************************************************************
 * Local Macros and Definitions
 **************************************************************************************************/

#define BATTERY_VOLTAGE_POLL_INTERVAL      1000

#define ADC_INIT_THUNDER_BOARD_REACT                                         \
  {                                                                          \
    adcOvsRateSel2,              /* 2x oversampling (if enabled). */         \
    adcWarmupNormal,             /* ADC shutdown after each conversion. */   \
    _ADC_CTRL_TIMEBASE_DEFAULT,  /* Use HW default value. */                 \
    2,                           /* Use a presc=2 => 38.4 / 3 = < 16 MHz. */ \
    false,                       /* Do not use tailgate. */                  \
    adcEm2Disabled               /* ADC disabled in EM2 */                   \
  }

/***************************************************************************************************
 * Local Type Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Local Variables
 **************************************************************************************************/

static uint32_t batteryVoltage;

/***************************************************************************************************
 * Public Variable Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Static Function Declarations
 **************************************************************************************************/

/***********************************************************************************************//**
 * @brief ADC Initialization
 **************************************************************************************************/
static void adcInit(void)
{
  ADC_Init_TypeDef       init       = ADC_INIT_THUNDER_BOARD_REACT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  // Enable ADC clock
  CMU_ClockEnable(cmuClock_ADC0, true);

  // Initiate ADC peripheral
  ADC_Init(ADC0, &init);

  // Setup single conversions
  initSingle.acqTime = adcAcqTime16;
  initSingle.reference = adcRef5VDIFF;
  initSingle.posSel = adcPosSelAVDD;
  initSingle.negSel = adcNegSelVSS;
  ADC_InitSingle(ADC0, &initSingle);
}

static uint32_t measureOneAdcSample(void)
{
  uint32_t adcData;

  ADC_Start(ADC0, adcStartSingle);
  while ((ADC_IntGet(ADC0) & ADC_IF_SINGLE) != ADC_IF_SINGLE) {
  }
  adcData = ADC_DataSingleGet(ADC0);

  return adcData;
}

static uint32_t measureBatteryVoltage(void)
{
  uint32_t adcData;
  uint32_t batteryVoltage;

  adcInit();
  adcData = measureOneAdcSample();
  batteryVoltage = (adcData * 5000 / 4096);

  return batteryVoltage;
}

/***************************************************************************************************
 * Public Function Definitions
 **************************************************************************************************/
void batteryMeasure(void)
{
  batteryVoltage = measureBatteryVoltage();
}

uint8_t batteryDeviceReadBatteryLevel(void)
{
  uint8_t batteryLevel;

  batteryLevel = cr2032_CalculateLevel(batteryVoltage);

  return batteryLevel;
}

/***************************************************************************************************
 * Static Function Definitions
 **************************************************************************************************/

/** @} (end addtogroup battery-hw) */
/** @} (end addtogroup app_hardware) */
