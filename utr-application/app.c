/***************************************************************************//**
 * @file
 * @brief Application file
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

/* Own header */
#include "app.h"

/* standard library headers */
#include <stdbool.h>

/* Board specific headers */
#include "rd0057.h"

/* Application specific headers */
#include "app_timer.h"
#include "app_ble.h"
#include "app_interrupt.h"
#include "app_ble_adv.h"
#include "app_ui.h"

#include "accori_device.h"
#include "csc_device.h"
#include "aluv_device.h"
#include "rht_device.h"
#include "aio_device.h"
#include "battery_device.h"

/**********************************************************************************************//**
 * @addtogroup Thunderboard
 * @{
 *************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup tbr_app
 * @{
 **************************************************************************************************/

/***************************************************************************************************
 * Local Macros and Definitions
 **************************************************************************************************/

#if (EMBER_AF_BOARD_TYPE != RD_0057_0101)
#error This sample application runs only on the RD-0057-0101 ThunderBoard-React
#endif

#define ADV_TIMEOUT_MS              30000

/***************************************************************************************************
 * Local Variables
 **************************************************************************************************/

static bool sleeping;

/***************************************************************************************************
 * Public Variable Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Local Functions
 **************************************************************************************************/
static uint8_t deviceCheck(void)
{
  uint8_t status = 0;
  status += accoriDeviceTest();
  status += aluvDeviceTest();
  status += rhtDeviceTest();
  return status;
}

static void advStart(void)
{
  appBleAdvStart();
  appUiAdvStarted();
  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(ADV_TIMEOUT_MS), ADV_TIMEOUT_TIMER, true);
}

static void sleep(void)
{
  appBleAdvStop();

  aluvDeviceSleep();
  rhtDeviceSleep();
  cscDeviceSleep();
  accoriDeviceSleep();
  aioDeviceSleep();
  appUiSleep();

  sleeping = true;
}

static void buttonHandler(uint8_t buttonNo, bool pushed)
{
  if (!sleeping) {
    aioServiceDigitalInUpdate();
  }

  if (pushed) {
    if (sleeping) {
      sleeping = false;
      advStart();
    }
  }
}

/***************************************************************************************************
 * Function Definitions
 **************************************************************************************************/
void appInit(void)
{
  appBleInit();

  /* App Interrupt init */
  appInterruptInit();

  // Initialize devices
  aluvDeviceInit();
  rhtDeviceInit();
  cscDeviceInit();
  accoriDeviceInit();
  aioDeviceInit();
  batteryDeviceInit();

  // Register calbacks for button pushes
  boardRegisterButtonCallback(&buttonHandler);

  appUiInit();

  if (deviceCheck()) {
    appUiError();
  } else {
    sleep();
  }
}

void appConnectionClosedEvent(uint8_t connection, uint16_t reason)
{
  aluvDeviceConnectionClosed();
  rhtDeviceConnectionClosed();
  cscDeviceConnectionClosed();
  accoriDeviceConnectionClosed();
  batteryDeviceConnectionClosed();

  appUiAdvStarted();

  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(ADV_TIMEOUT_MS), ADV_TIMEOUT_TIMER, true);
}

void appConnectionOpenedEvent(uint8_t connection, uint8_t bonding)
{
  gecko_cmd_hardware_set_soft_timer(0, ADV_TIMEOUT_TIMER, false);

  aluvDeviceConnectionOpened();
  rhtDeviceConnectionOpened();
  cscDeviceConnectionOpened();
  accoriDeviceConnectionOpened();
  batteryDeviceConnectionOpened();

  appUiConnectionOpened();
}

void appAdvTimeoutEvtHandler()
{
  sleep();
}

/** @} (end addtogroup tbr_app) */
/** @} (end addtogroup Thunderboard) */
