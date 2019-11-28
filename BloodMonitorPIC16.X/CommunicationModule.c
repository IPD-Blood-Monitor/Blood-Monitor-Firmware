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


/****************************************************************************
 Forward Declarations
****************************************************************************/
I2C1_MESSAGE_STATUS i2cMessageStatus;

/****************************************************************************
 Public Functions
****************************************************************************/
/**
   @Description
 initialized the communicationmodule 

   @Preconditions
    I2C1_Initialize() should have been called

   @Param
 *  none

   @Returns
 none
 */
void initializeCommunicationModule(void)
{
    int i; 
    
    // empty the send data array
    for(i = 0; i < SEND_DATA_ARR_LEN; i++)
    {
        sendDataArr[i] = SEND_DATA_ARR_DEFAULT_VAL;
    }
    
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
bool sendDataArrayI2C(uint16_t deviceAddress)
{
    // return variable 
    bool returnVal = false;
    
    // check if max 10bit address
    if (deviceAddress > 1023)
        return returnVal;
    
    // send the data over I2C
    I2C1_MasterWrite(
                                &sendDataArr,
                                SEND_DATA_ARR_LEN,
                                deviceAddress,
                                &i2cMessageStatus);
    // if went ok 
    returnVal = true;
    
    // return
    return returnVal;
}

/****************************************************************************
Private Functions
****************************************************************************/