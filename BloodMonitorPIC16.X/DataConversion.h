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
 * Author: Cis van Mierlo
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_DATACONVERSION_H
#define	XC_DATACONVERSION_h
/****************************************************************************
 Includes
****************************************************************************/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
/****************************************************************************
 Defines
****************************************************************************/
typedef enum 
{
    w660 = 0,
    w850 = 1,
    w940 = 2,
}Wavelenght_t;

// The Callbackfunction for if the data needs to be send
typedef void (*changeWaveCallbackFunction)(void);

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
 *  the address of the callbackfunction called when the new wavelenght needs to be selected

   @Returns
     None
 */
void initializeDataConversion(changeWaveCallbackFunction p_changeWaveCallbackFunction);

/**
   @Description
 * this function need to be called in the main loop 

   @Preconditions
     initializeDataConversion() function should have been called 
         before calling this function.

   @Param
 * none

   @Returns
     None
 */
void dataConversionTick(void);

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
void startDataCapture(void);

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
uint16_t getResultArrData(char index);

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
void setWavelenght(Wavelenght_t newWavelenght);

void dataConversionTick(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

