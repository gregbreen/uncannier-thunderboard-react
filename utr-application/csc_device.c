/***************************************************************************//**
 * @file
 * @brief Cycling Speed and Cadence Device
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

#include "csc_device.h"
/* standard libraries */
#include <stdint.h>
#include <stdbool.h>

/* EM lib */
#include "em_rtcc.h"
#include "em_cmu.h"
#include "em_cryotimer.h"

#include "rd0057.h"

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup csc_hw
 * @{
 **************************************************************************************************/

/***************************************************************************************************
 * Local Macros and Definitions
 **************************************************************************************************/

#define REVOLUTION_TIMESTAMP_TIMESCALE_HZ   1024
#define CRYOTIMER_CNT_CLOCK_HZ             32768 // Directly from LFXO

/***************************************************************************************************
 * Local Type Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Local Variables
 **************************************************************************************************/

static uint32_t wheelRevolutions = 0;
static uint32_t timeStamp = 0;
static bool firstWheelRevRead = false;

/***************************************************************************************************
 * Static Function Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Public Function Definitions
 **************************************************************************************************/
void cscDeviceInit(void)
{
  CRYOTIMER_Init_TypeDef cryoInit = CRYOTIMER_INIT_DEFAULT;
  cryoInit.osc = cryotimerOscLFXO;

  timeStamp = 0;
  wheelRevolutions = 0;

  // Use Cryo Timer to use for timestamps
  CMU_ClockEnable(cmuClock_CRYOTIMER, true);
  CRYOTIMER_Init(&cryoInit); // Configure and enable
}

void cscDeviceDeInit(void)
{
  boardHallEnable(false);
}

void cscDeviceSleep(void)
{
  boardHallEnable(false);
}

void cscDeviceConnectionOpened(void)
{
}

void cscDeviceConnectionClosed(void)
{
  boardHallEnable(false);
}

void cscDeviceInterrupt(void)
{
  // Don't increment wheel count until first read has been done to avoid
  // spurious rev counts when sensor is powered on.
  if (firstWheelRevRead) {
    timeStamp = (uint16_t)(CRYOTIMER_CounterGet()
                           / (CRYOTIMER_CNT_CLOCK_HZ
                              / REVOLUTION_TIMESTAMP_TIMESCALE_HZ));
    wheelRevolutions++;
  }
}

void cscDeviceCharStatusChange(uint8_t connection, uint16_t clientConfig)
{
  /* if the new value of CCC is not 0 either indication or notification is enabled */
  if (clientConfig) {
    firstWheelRevRead = false;
    wheelRevolutions = 0;
    // Turn on hall sensor
    boardHallEnable(true);
  } else {
    firstWheelRevRead = false;
    // Turn off hall sensor
    boardHallEnable(false);
  }
}

void cscDeviceSetRevCount(uint32_t value)
{
  wheelRevolutions = value;
}

uint32_t cscDeviceReadWheelRevCount(void)
{
  firstWheelRevRead = true;
  return wheelRevolutions;
}

uint16_t cscDeviceReadLastWheelTime(void)
{
  return timeStamp;
}

uint16_t cscDeviceReadTotalCrankRevs(void)
{
  return 0;
}

uint16_t cscDeviceReadLastCrankRevTime()
{
  return 0;
}

/** @} (end addtogroup csc_hw) */
/** @} (end addtogroup app_hardware) */
