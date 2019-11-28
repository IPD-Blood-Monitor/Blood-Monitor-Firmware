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
#define MOVING_AVG_SIZE 8
#define AMOUNT_DIODES 2
#define AMOUNT_WAVELENGTHS 3

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
Wavelenght_t activeWavelenght = w660;

uint16_t movingAvgResultDWArr[AMOUNT_DIODES][AMOUNT_WAVELENGTHS];
uint16_t movingAvgRawDataDWArr[AMOUNT_DIODES][AMOUNT_WAVELENGTHS][MOVING_AVG_SIZE];
uint8_t movingAvgRawDataIndexDWArr[AMOUNT_DIODES][AMOUNT_WAVELENGTHS];

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
    int i = 0, j = 0, k = 0;
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
    // empty the moving average
    for(i = 0; i < AMOUNT_DIODES; i++)
    {
        for(j = 0; j < AMOUNT_WAVELENGTHS; j++)
        {
            movingAvgResultDWArr[i][j] = 0;
            movingAvgRawDataIndexDWArr[i][j] = 0;
            for(k = 0; k < MOVING_AVG_SIZE; k++)
            {
                movingAvgRawDataDWArr[i][j][k] = 0;
            }
        }
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
    
    //if (index < RESULT_ARRAY_SIZE)
    if (index < (AMOUNT_DIODES * AMOUNT_WAVELENGTHS))
    {
        // return the value
        //returnVal = resultBufferArr[index];
        returnVal = movingAvgResultDWArr[(int)(index/3)][index %3];
    }
    
    // return
    return returnVal;
}

/**
   @Description
 * this function is used to set a specific wavelenght

   @Preconditions
    none

   @Param
 *  what the new driven wavelenght is

   @Returns
    none
 */
void setWavelenght(Wavelenght_t newWavelenght)
{
    // set the new wavelenght
    activeWavelenght = newWavelenght;
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
    // save the result somewhere 
    rawResultArr[measState] = ADC_GetConversionResult();
    
    // increase the index for the raw data array (rotate)
    movingAvgRawDataIndexDWArr[measState>>1][activeWavelenght] = 
    (movingAvgRawDataIndexDWArr[measState>>1][activeWavelenght] + 1) % MOVING_AVG_SIZE;
    
    // set the new data in the raw data array
    movingAvgRawDataDWArr[measState>>1][activeWavelenght][movingAvgRawDataIndexDWArr[measState>>1][activeWavelenght]] 
    = rawResultArr[measState];
    
    // if faster calculation is possible
#ifdef MOVING_AVG_SIZE == 8
    // calculate new moving average 
    // by adding sample N and subtracting sample N-MOVING_AVG_SIZE (this is divided by MOVING_AVG_SIZE)
    movingAvgResultDWArr[measState>>1][activeWavelenght] = 
    movingAvgResultDWArr[measState>>1][activeWavelenght] +
    ((rawResultArr[measState] 
    - movingAvgRawDataDWArr[measState>>1][activeWavelenght][(movingAvgRawDataIndexDWArr[measState>>1][activeWavelenght]+1) % MOVING_AVG_SIZE])
    >> 3);
#else
    // calculate new moving average 
    // by adding sample N and subtracting the N-MOVING_AVG_SIZE sample (this is divided by MOVING_AVG_SIZE)
    movingAvgResultDWArr[measState>>1][activeWavelenght] = 
    movingAvgResultDWArr[measState>>1][activeWavelenght] +
    ((rawResultArr[measState] 
    - movingAvgRawDataDWArr[measState>>1][activeWavelenght][(movingAvgRawDataIndexDWArr[measState>>1][activeWavelenght]+1) % MOVING_AVG_SIZE])
    / MOVING_AVG_SIZE);
#endif
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