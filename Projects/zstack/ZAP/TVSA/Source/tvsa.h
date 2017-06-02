/**************************************************************************************************
    Filename:       tvsa.h
    Revised:        $Date: 2011-07-25 20:23:05 -0700 (Mon, 25 Jul 2011) $
    Revision:       $Revision: 26899 $

    Description:

    This file implements the Temperature/Voltage Sample Application.


    Copyright 2009 Texas Instruments Incorporated. All rights reserved.

    IMPORTANT: Your use of this Software is limited to those specific rights
    granted under the terms of a software license agreement between the user
    who downloaded the software, his/her employer (which must be your employer)
    and Texas Instruments Incorporated (the "License").  You may not use this
    Software unless you agree to abide by the terms of the License. The License
    limits your use, and you acknowledge, that the Software may not be modified,
    copied or distributed unless embedded on a Texas Instruments microcontroller
    or used solely and exclusively in conjunction with a Texas Instruments radio
    frequency transceiver, which is integrated into your product.  Other than for
    the foregoing purpose, you may not use, reproduce, copy, prepare derivative
    works of, modify, distribute, perform, display or sell this Software and/or
    its documentation for any purpose.

    YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
    PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
    INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
    NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
    TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
    NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
    LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
    OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
    OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

    Should you have any questions regarding your right to use this Software,
    contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/
#ifndef TVSA_H
#define TVSA_H

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "hal_board_cfg.h"
#include "ZComDef.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Constants
 * ------------------------------------------------------------------------------------------------
 */

// Expanding on a TI proprietary Profile Id used for Z-Accel / ZASA / CC2480.
#define TVSA_PROFILE_ID            0x0F10
#define TVSA_CLUSTER_ID            0x0002
#define TVSA_CLUSTER_CNT           1
#define TVSA_DEVICE_VERSION        0
#define TVSA_FLAGS                 0
 
#define TVSA_ENDPOINT              3

#if !defined TVSA_DEVICE_ID
// Master for CC2480 ZASA reports sets to zero.
#if defined HAL_BOARD_CC2430BB
#define TVSA_DEVICE_ID             0x0001
#elif defined HAL_BOARD_CC2430DB
#define TVSA_DEVICE_ID             0x0002
#elif defined HAL_BOARD_CC2430EB
#define TVSA_DEVICE_ID             0x0003
#elif defined HAL_BOARD_CC2530EB_REV13
#define TVSA_DEVICE_ID             0x0004
#elif defined HAL_BOARD_CC2530EB_REV17
#define TVSA_DEVICE_ID             0x0005
#elif defined HAL_BOARD_F5438
#define TVSA_DEVICE_ID             0x0006
#elif defined HAL_BOARD_F2618
#define TVSA_DEVICE_ID             0x0007
#else

//efine TVSA_DEVICE_ID             0x0016  // ZAP pre-defined for MSP5438-CC2530EM
//efine TVSA_DEVICE_ID             0x0017  // ZAP pre-defined for MSP2618-CC2530EM

#error Unexpected HAL_BOARD - need specific Temp/Volt conversion from specific A2D channel.
#endif
#endif

#if !defined TVSA_DONGLE
#define TVSA_DONGLE                FALSE
#endif

#if !defined TVSA_DONGLE_IS_ZC
#define TVSA_DONGLE_IS_ZC          TRUE
#endif

// Bit values for the TVSA_OPT_IDX.
#define TVSA_OPT_SRC_RTG           0x01

#define TVSA_DAT_LEN               16

#define TVSA_CMD_IDX               0
#define TVSA_IEE_IDX               1
#define TVSA_PAR_LSB               9
#define TVSA_PAR_MSB               10
#define TVSA_TEM_IDX               11
#define TVSA_BUS_IDX               12
#define TVSA_TYP_IDX               13
#define TVSA_OPT_IDX               14
#define TVSA_RTG_IDX               15

#define TVSA_ADR_LSB               1
#define TVSA_ADR_MSB               2

#if TVSA_DONGLE
#define TVSA_SOP_VAL               0xFE
#define TVSA_PORT                  0
#define SOP_STATE                  0
#define CMD_STATE                  1
#define FCS_STATE                  2

#define TVSA_SOP_IDX               0
#define TVSA_DAT_OFF               TVSA_ADR_MSB+1
// Not adding +1 for FCS because 1st byte of message is skipped - CMD is always 0 for data.
#define TVSA_BUF_LEN               TVSA_DAT_LEN+TVSA_DAT_OFF
#define TVSA_FCS_IDX               TVSA_BUF_LEN-1
#endif

// TVSA Command set.
#define TVSA_CMD_DAT               0  // TVSA data message.
#define TVSA_CMD_BEG               1  // Start reporting TVSA data.
#define TVSA_CMD_END               2  // Stop reporting TVSA data.

#define TVSA_EVT_ANN               0x4000
#define TVSA_EVT_DAT               TVSA_EVT_ANN  /* Mutually exclusive use by TVSA_DONGLE. */
#define TVSA_EVT_REQ               0x2000

#define TVSA_DLY_ANN               60000
#define TVSA_DLY_DAT               TVSA_DLY_ANN
// Attempt to randomly stagger reports within the reporting window.
#define TVSA_STG_DAT               ((uint16)(((uint32)TVSA_DLY_DAT * Onboard_rand()) / 65536))
#define TVSA_DLY_MIN               5000  // Minimum delay (also in case TVSA_STG_DAT returns 0).

#if !defined TVSA_SRC_RTG
#define TVSA_SRC_RTG               FALSE
#endif

#if TVSA_SRC_RTG
// Source routing requires special builds of the ZNP with the following settings:
// #define ZIGBEE_SOURCE_ROUTING
// #define ZIGBEE_MANY_TO_ONE
// SRC_RTG_EXPIRY_TIME must be greater than TVSA_DLY_DAT.
// #if TVSA_DONGLE
// #define CONCENTRATOR_ENABLE  TRUE
// CONCENTRATOR_DISCOVERY_TIME must be globally defined to be less than or equal to TVSA_DLY_DAT.
// #endif
#endif

#define TVSA_DATA_CNF              TRUE

/* ------------------------------------------------------------------------------------------------
 *                                          Macros
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                           Global Variables
 * ------------------------------------------------------------------------------------------------
 */

#if TVSA_DATA_CNF
extern uint8 tvsaCnfErrCnt;
#endif
extern uint8 tvsaTaskId;

/* ------------------------------------------------------------------------------------------------
 *                                          Functions
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 * @fn          tvsaAppInit
 *
 * @brief       This function is the application's task initialization.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void tvsaAppInit(uint8 id);

/**************************************************************************************************
 * @fn          tvsaAppEvt
 *
 * @brief       This function is called to process the OSAL events for the task.
 *
 * input parameters
 *
 * @param       id - OSAL task Id.
 * @param       evts - OSAL events bit mask of pending events.
 *
 * output parameters
 *
 * None.
 *
 * @return      evts - OSAL events bit mask of unprocessed events.
 **************************************************************************************************
 */
uint16 tvsaAppEvt(uint8 id, uint16 evts);

#endif
/**************************************************************************************************
*/
