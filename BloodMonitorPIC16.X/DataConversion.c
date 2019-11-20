/*
 * File:   DataConversion.c
 * Author: cisvm
 *
 * Created on November 14, 2019, 12:16 PM
 */

/****************************************************************************
 Includes
****************************************************************************/
#include <xc.h>
#include "DataConversion.h"
//#include "adc.h" 
//#include ?mcc_generated_files/mcc.h?
#include "mcc_generated_files/mcc.h"

/****************************************************************************
 Defines
****************************************************************************/
#define RESULT_ARRAY_SIZE 4
// enum to know which diode is being used 
typedef enum{
 diode1 = channel_ANC0,
 diode2 = channel_ANC1
}ADCChannel_t;

typedef enum{
 diode1H = 0,
 diode1L = 1,
 diode2H = 2,
 diode2L = 3
}measureState_t;

#define AMOUNT_DATA_CONV_FOR_SEND 4
//// struct to store the high and low raw diode values in
//typedef struct
//{
//    adc_result_t high;
//    adc_result_t low;
//}flankResult_t;
//
//// struct to store the raw diode values in
//typedef struct
//{
//    flankResult_t diode1;
//    flankResult_t diode2;
//}rawResult_t;

/****************************************************************************
 Forward Declarations
****************************************************************************/
ADCChannel_t currentDiodeMes = diode1;
//rawResult_t rawResult;
measureState_t measState;
adc_result_t rawResultArr[RESULT_ARRAY_SIZE];
static uint16_t resultBufferArr[RESULT_ARRAY_SIZE] = {0, 0, 0, 0};
bool I2CTransmissionBusy = false;
uint8_t dataConversions = 0;
sendDataCallbackFunction p_sendDataCallbackFunctionfp;
bool sendDataCallbackFunctionConnected = false;

/**
   @Description
 * this function is called when the ADC is done with the conversion 

   @Preconditions
 it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void adcConversionDone(void);

/****************************************************************************
 Public Functions
****************************************************************************/
/**
   @Description
 * this function is needed to initialize the dataconversion and to start data acqusision 

   @Preconditions
     IADC_Initialize() function should have been called 
         before calling this function.

   @Param
 *  the address of the callbackfunction called when data needs to be send

   @Returns
     None
 */
void initializeDataConversion(sendDataCallbackFunction p_sendDataCallbackFunction)
{
    int i = 0;
    //connect the callback function
    ConnectCallbackFunction(&adcConversionDone);
    p_sendDataCallbackFunctionfp = p_sendDataCallbackFunction;
    sendDataCallbackFunctionConnected = true;
    
    //empty the rawresult struct
//    rawResult.diode1.high = 0;
//    rawResult.diode1.low = 0;
//    rawResult.diode2.high = 0;
//    rawResult.diode2.low = 0;
    for(i = 0; i < RESULT_ARRAY_SIZE; i++)
    {
        rawResultArr[i] = 0;
    }
    
    // start with the first Diode
    currentDiodeMes = diode1;
}

/**
   @Description
 * this function is used to start the data capture on the next channel

   @Preconditions
     initializeDataConversion() function should have been called 
         before calling this function.

   @Param
 *  bool if the PWMpin is high

   @Returns
     None
 */
void startDataCapture(bool highFlank)
{
    // Set the channel
    ADC_SelectChannel((adc_channel_t)currentDiodeMes);
    
    // set the measure state
    if(currentDiodeMes == diode1)
        measState = !highFlank;
    else
        measState = !highFlank + 2;
    
    // capture ADC value
    ADC_StartConversion();
}

/**
   @Description
 * this function is used to get data from the result data array

   @Preconditions
    none

   @Param
 *  the index number of the array; shouldn't be more than the elements - 1

   @Returns
    returns the value in the array
 */
uint16_t getResultArrData(char index)
{
    // send max value if not correct
    uint16_t returnVal = UINT16_MAX;
    
    if (index < RESULT_ARRAY_SIZE)
    {
        // return the value
        returnVal = resultBufferArr[index];
    }
    
    // return
    return returnVal;
}
/****************************************************************************
Private Functions
****************************************************************************/
/**
   @Description
 * this function is called when the ADC is done with the conversion 

   @Preconditions
 it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void adcConversionDone(void)
{
    // save the result
    rawResultArr[measState] = ADC_GetConversionResult();
    if (!I2CTransmissionBusy)
    {
        // copy the array as long as there is no I2C transmission
        resultBufferArr[measState] = rawResultArr[measState];
        
        // increase the amount of data conversion
        dataConversions++;
    }
    
    // if the ammount of dataConversion is reached to send it
    if (dataConversions >= AMOUNT_DATA_CONV_FOR_SEND)
    {
        // the transmission is busy
        I2CTransmissionBusy = true;
        
        // send the data
        if(sendDataCallbackFunctionConnected)
            p_sendDataCallbackFunctionfp();
        
        // reset the counter
        dataConversions = 0;
    }
    
    
    //change the channel if the low measState has occurred
    if(measState%2 == 1)
    {
        if(currentDiodeMes == diode1)
            currentDiodeMes = diode2;
        else 
            currentDiodeMes = diode1;
    }
    
//    // check which diode is measured
//    if(currentDiodeMes == diode1)
//    {
//        // save Diode value
//        rawResult.diode1 = ADC_GetConversionResult();
//        
//        // set the other diode to be measured
//        currentDiodeMes = diode2;
//
//        // Set the channel
//        ADC_SelectChannel(currentDiodeMes);
//
//        // capture ADC value
//        ADC_StartConversion();
//        
//    }
//    else
//    {
//        // save Diode value
//        rawResult.diode2 = ADC_GetConversionResult();
//        
//        // call function that the raw data is collected
//        
//    }
}