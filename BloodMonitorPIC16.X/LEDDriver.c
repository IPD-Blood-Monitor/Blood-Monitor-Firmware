/*
 * File:   LEDDriver.c
 * Author: cisvm
 *
 * Created on November 14, 2019, 12:16 PM
 */

/****************************************************************************
 Includes
****************************************************************************/
#include <xc.h>
#include "LEDDriver.h"
//#include "pwm5.h"
#include "mcc_generated_files/mcc.h"
//#include "tmr2.h"
//#include "pin_manager.h"

/****************************************************************************
 Defines
****************************************************************************/
#define PERIOD_COUNT_FOR_CHANGE 30000 // frequency of the PWM so 1s
typedef enum 
{
    LED660 = 0,
    LED850 = 1,
    LED940 = 2,
    NOLED  = 3
}MUXChannel_t;

measureInputCallbackFunction p_measureInputCallbackFunctionfp;
bool pwmChangeCallbackFunctionConnected  = false;
unsigned int periodCount = UINT16_MAX;
MUXChannel_t currentLED = NOLED;
/****************************************************************************
 Forward Declarations
****************************************************************************/
/**
   @Description
 * this function can be used to change the mux channel from 1 up to 4

   @Preconditions
     InitializeLEDDriver() function should have been called 
         before calling this function.

   @Param
 *  the new LED of the mux as an MUXChannel_t

   @Returns
     None
 */
void changeMux(MUXChannel_t LED);

/**
   @Description
 * this function is the new timer2 interrupt handler

   @Preconditions
    TMR2_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer2InterruptHandler(void);

/**
   @Description
 * this function is the new timer3 interrupt handler

   @Preconditions
    TMR3_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer3InterruptHandler(void);

/**
   @Description
 * this function is the new timer4 interrupt handler

   @Preconditions
    TMR4_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer4InterruptHandler(void);

/****************************************************************************
 Public Functions
****************************************************************************/

/**
   @Description
    initializes and starts the LED Driver to drive the MUX 
 *  and if the usePWMUc is true the PWM is module is started
 *  otherwise the GPIO interrupt is enabled

   @Preconditions
     SYSTEM_Initialize() function should have been called 
         before calling this function.

   @Param
 *  if the PWM module of the microcontroller is used
 *  address of the callback function to the pwm change function

   @Returns
     None
 */
void InitializeLEDDriver(bool UsePWMUc, measureInputCallbackFunction p_measureInputCallbackFunction)
{
    // connect the callback function
    p_measureInputCallbackFunctionfp = p_measureInputCallbackFunction;
    pwmChangeCallbackFunctionConnected = true;
    
    // connect all the new interrupt handlers
    TMR2_SetInterruptHandler(&timer2InterruptHandler); 
    TMR3_SetInterruptHandler(&timer3InterruptHandler);
    TMR4_SetInterruptHandler(&timer4InterruptHandler);
    
    // initialze the GPIO pins
    PIN_MANAGER_Initialize();
    
    // turn off the mux by selecting the 4th channel
    currentLED = NOLED;
    changeMux(currentLED);
    
    // start the PWM
    TMR2_StartTimer();
    
    // set the period count that it will switch on next LED after first period
    periodCount = PERIOD_COUNT_FOR_CHANGE;    
}







/****************************************************************************
Private Functions
****************************************************************************/
/**
   @Description
 * this function can be used to change the mux channel from 1 up to 4

   @Preconditions
     InitializeLEDDriver() function should have been called 
         before calling this function.

   @Param
 *  the new LED of the mux as an MUXChannel_t

   @Returns
     None
 */
void changeMux(MUXChannel_t LED)
{
    switch(LED)
    {
        case LED660:
            IO_RA2_SetLow();
            IO_RC2_SetLow();
        break;
        case LED850:
            IO_RA2_SetHigh();
            IO_RC2_SetLow();
            
        break;
        case LED940:
            IO_RA2_SetLow();
            IO_RC2_SetHigh();
        break;
        case NOLED:
            IO_RA2_SetHigh();
            IO_RC2_SetHigh();
        break;
    }
}
/**
   @Description
 * this function is the new timer2 interrupt handler

   @Preconditions
    TMR2_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer2InterruptHandler(void)
{
    // up the counter
    periodCount++;
    
    // check if LED should change
    if (periodCount >= PERIOD_COUNT_FOR_CHANGE)
    {
        // change the mux that drives the LEDS
        currentLED = (currentLED + 1) % 3;
        changeMux(currentLED);
        
        // reset period count
        periodCount = 0;
    }
               
    // start timer 4
    TMR4_StartTimer();
}

/**
   @Description
 * this function is the new timer3 interrupt handler

   @Preconditions
    TMR3_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer3InterruptHandler(void)
{
    // stop the timer
    TMR3_StopTimer();
    
    // call the pwm change callbackfunction
    p_measureInputCallbackFunctionfp();
}

/**
   @Description
 * this function is the new timer4 interrupt handler

   @Preconditions
    TMR4_Initialize() should have been called

   @Param
 *  none

   @Returns
     None
 */
void timer4InterruptHandler(void)
{
    // stop the timer
    TMR4_StopTimer();
    
    // start timer 3
    TMR3_StartTimer();
    
    // call the pwm change callbackfunction
    p_measureInputCallbackFunctionfp();
}