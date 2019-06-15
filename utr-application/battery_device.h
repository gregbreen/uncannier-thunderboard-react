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

#ifndef BATTERY_HW_H
#define BATTERY_HW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************//**
 * \defgroup battery-hw Battery HW
 * \brief Battery Service HW API
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup battery-hw
 * @{
 **************************************************************************************************/

/***************************************************************************************************
 * Public Macros and Definitions
 **************************************************************************************************/

/***********************************************************************************************//**
 *  @brief
 *    This macro has been defined to let the batt service read the battery
 *    level with the function in this module.
 **************************************************************************************************/
#define appHwReadBatteryLevel()         batteryDeviceReadBatteryLevel()

/***************************************************************************************************
 * Function Declarations
 **************************************************************************************************/

/***********************************************************************************************//**
 *  @brief
 *    Measure the battery voltage.
 **************************************************************************************************/
void batteryMeasure(void);

/***********************************************************************************************//**
 *  @brief
 *    Calculate the battery level in % based on the filtered battery voltage.
 *    It is assumed a very low current consumption and a CR2032 battery.
 **************************************************************************************************/
uint8_t batteryDeviceReadBatteryLevel(void);

/** @} (end addtogroup battery-hw) */
/** @} (end addtogroup app_hardware) */

#ifdef __cplusplus
};
#endif

#endif // BATTERY_HW_H
