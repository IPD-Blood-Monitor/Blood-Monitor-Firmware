/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_COMMUNICATIONMODULE_H
#define	XC_COMMUNICATIONMODULE_H
/****************************************************************************
 Includes
****************************************************************************/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include "I2CDriver.h"
/****************************************************************************
 Defines
****************************************************************************/
#define SEND_DATA_ARR_LEN 12
#define SEND_DATA_ARR_DEFAULT_VAL 1
/****************************************************************************
 Public Variables
****************************************************************************/
// this array contains the data to be send 
uint8_t sendDataArr[SEND_DATA_ARR_LEN]; 
typedef void (*getDataCallbackFunction)(void);


/****************************************************************************
 Public Functions
****************************************************************************/
/**
   @Description
 initialized the communicationmodule 

   @Preconditions
    I2C1_Initialize() should have been called

   @Param
 *  the I2C address
 * the address of the function to set the data in the send data array 

   @Returns
 none
 */
void initializeCommunicationModule(uint8_t I2CAddress, getDataCallbackFunction p_getDataCallbackFunction);

/**
   @Description
    sends the sendDataArr over the I2C1 bus to the specified address

   @Preconditions
    sendDataArrayI2C() should have been called

   @Param
 *  the address of the I2C

   @Returns
 true if succeeded
 */
//bool sendDataArrayI2C(uint16_t deviceAddress);

/**
   @Description
    Starts the timer to send data every x times 50ms

   @Preconditions
    initializeCommunicationModule() should have been called

   @Param
 *  the amount of time to send new data times 50ms

   @Returns
 true if succeeded
 */
bool StartI2CSender(uint32_t transmissionTimeX50ms);

/**
   @Description
    stops the timer to send data every x times 50ms

   @Preconditions
    initializeCommunicationModule() should have been called

   @Param

   @Returns
 true if succeeded
 */
bool StopI2CSender(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

