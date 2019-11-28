/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18325
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "CommunicationModule.h"
#include "DataConversion.h"
#include "LEDDriver.h"

#define PWMUCGEN true
#define ADCUCACQ true
#define ARDUINO_ADDRESS 0x08

//letop 5V voeden vanuitpic staat aan!!!!!
/**
   @Description
 * this function is called when the input signal needs to be measured timeBased

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void measureInputDiodeTimeCallbackFunction(void);

/**
   @Description
 * this function is called when new data should be send

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void SendDataCallbackFunction(void);

/**
   @Description
 * this function is called when an other diode is selected

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void otherLEDDrivedCallbackFunction(MUXChannel_t newWavelenght);

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // initial LED driver
    InitializeLEDDriver(PWMUCGEN, &measureInputDiodeTimeCallbackFunction, &otherLEDDrivedCallbackFunction);
    
    // initialize data conversion
    initializeDataConversion(&SendDataCallbackFunction);
    
    // initialize the communication module
    
   
    while (1)
    {
        // Add your application code
    }
}

/**
   @Description
 * this function is called when the input signal needs to be measured timeBased

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void measureInputDiodeTimeCallbackFunction(void)
{
    bool pwmVal = RC3_GetValue();
    // check high low and start data capture
    startDataCapture(pwmVal);
}

/**
   @Description
 * this function is called when new data should be send

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void SendDataCallbackFunction(void)
{
    // copy the array in the send array
    for(int i = 0; i < SEND_DATA_ARR_LEN; i++)
    {
        // conversion from 16 bit to 8 bit
        if (i%2 == 0)
        {
            // get the MSB
            sendDataArr[i] = (uint8_t)((getResultArrData((char)(i/2)) >> 8 ) & UINT8_MAX);
        }
        else
        {
            // get the LSB
            sendDataArr[i] = (uint8_t)(getResultArrData((char)(i/2)) & UINT8_MAX);
        }
    }
    
    // send the data
    sendDataArrayI2C((char)ARDUINO_ADDRESS);
}

/**
   @Description
 * this function is called when an other diode is selected

   @Preconditions
    it needs to be connected 

   @Param
 *  none

   @Returns
     None
 */
void otherLEDDrivedCallbackFunction(MUXChannel_t newWavelenght)
{
    // check if the conversion can be done
    if(newWavelenght < 3)
        // set the data to the data conversion module
        setWavelenght((Wavelenght_t)newWavelenght);
}

/**
 End of File
*/