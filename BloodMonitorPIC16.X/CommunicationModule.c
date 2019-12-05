/*
 * File:   CommunicationModule.c
 * Author: cisvm
 *
 * Created on November 14, 2019, 12:16 PM
 */


#include <xc.h>
#include "CommunicationModule.h"
#include "mcc_generated_files/mcc.h"
/****************************************************************************
 Includes
****************************************************************************/


/****************************************************************************
 Defines
****************************************************************************/
#define SECOND 20
#define DEFAULT_TRANSMISSION_TIMER_COUNT SECOND

/****************************************************************************
 Forward Declarations
****************************************************************************/
//I2C1_MESSAGE_STATUS i2cMessageStatus;

/**
   @Description
 * this function is the new timer5 interrupt handler

   @Preconditions
    TMR5_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer5InterruptHandler(void);

uint32_t transmissionTimerCounter = DEFAULT_TRANSMISSION_TIMER_COUNT;
uint32_t transmissionTimerCounterVal = 0;
uint8_t adruinoAddress = 0;
getDataCallbackFunction p_getDataCallbackFunctionfp;
bool getDataCallbackFunctionConnected = false;

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
void initializeCommunicationModule(uint8_t I2CAddress, getDataCallbackFunction p_getDataCallbackFunction)
{
    // connect the callback function
    p_getDataCallbackFunctionfp = p_getDataCallbackFunction;
    getDataCallbackFunctionConnected = true;
    
    I2C1_Initialize();
    
    int i; 
    
    // set the address
    adruinoAddress = I2CAddress;
    
    // empty the send data array
    for(i = 0; i < SEND_DATA_ARR_LEN; i++)
    {
        sendDataArr[i] = SEND_DATA_ARR_DEFAULT_VAL;
    }
    
    // connect interrupt handler
    TMR5_SetInterruptHandler(&timer5InterruptHandler);
    
}



/**
   @Description
    sends the sendDataArr over the I2C1 bus to the specified address

   @Preconditions
    I2C1_Initialize() should have been called

   @Param
 *  the address of the I2C

   @Returns
 if failed
 */
//bool sendDataArrayI2C(uint16_t deviceAddress)
//{
//    // return variable 
//    bool returnVal = false;
//    
//    // check if max 10bit address
//    if (deviceAddress > 1023)
//        return returnVal;
//    
//    // send the data over I2C
//    I2C1_MasterWrite(
//                                &sendDataArr,
//                                SEND_DATA_ARR_LEN,
//                                deviceAddress,
//                                &i2cMessageStatus);
//    // if went ok 
//    returnVal = true;
//    
//    // return
//    return returnVal;
//}

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
bool StartI2CSender(uint32_t transmissionTimeX50ms)
{
    if (transmissionTimeX50ms != 0)
        transmissionTimerCounter = transmissionTimeX50ms;
    
    TMR5_StartTimer();
}

/**
   @Description
    stops the timer to send data every x times 50ms

   @Preconditions
    initializeCommunicationModule() should have been called

   @Param

   @Returns
 true if succeeded
 */
bool StopI2CSender(void)
{
    TMR5_StopTimer();
}

/****************************************************************************
Private Functions
****************************************************************************/

/**
   @Description
 * this function is the new timer5 interrupt handler

   @Preconditions
    TMR5_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer5InterruptHandler(void)
{
    // up the counter
    transmissionTimerCounterVal++;
    
    // check if overwritten
    if(transmissionTimerCounterVal >= transmissionTimerCounter)
    {
//        // set the data 
//        if (getDataCallbackFunctionConnected)
//            p_getDataCallbackFunctionfp();      
        
        // send the data
        I2C1_MasterWriteNbitsCisOperation(adruinoAddress, sendDataArr, SEND_DATA_ARR_LEN);
        transmissionTimerCounterVal = 0;
    }
}