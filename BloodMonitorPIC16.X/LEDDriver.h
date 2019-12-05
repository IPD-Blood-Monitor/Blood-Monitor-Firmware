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
#ifndef XC_LEDDRIVER_H
#define	XC_LEDDRIVER_H

/****************************************************************************
 Includes
****************************************************************************/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

/****************************************************************************
 Defines
****************************************************************************/
typedef enum 
{
    LED660 = 0,
    LED850 = 1,
    LED940 = 2,
    NOLED  = 3
}MUXChannel_t;

// The Callbackfunction for if the ADC is done
//typedef void (*measureInputCallbackFunction)(void);
typedef void (*changeLEDCallbackFunction)(MUXChannel_t newWavelenght);

/****************************************************************************
 Public Functions
****************************************************************************/
/**
   @Description
    initializes and starts the LED Driver to drive the MUX 
 *  otherwise the GPIO interrupt is enabled

   @Preconditions
     SYSTEM_Initialize() function should have been called 
         before calling this function.

   @Param
 *  if the an other LED is selected with the MUX
 *  address of the callback function to the LED change function

   @Returns
     None
 */
void InitializeLEDDriver(changeLEDCallbackFunction p_changeLEDCallbackFunction);

/**
   @Description
 * this selects the next wavelenght

   @Preconditions
     InitializeLEDDriver() function should have been called 
         before calling this function.

   @Param
 *  none

   @Returns
     None
 */
void SelectNextWavelenght(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

