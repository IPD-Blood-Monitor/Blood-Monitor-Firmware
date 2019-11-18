/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18325
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA2 aliases
#define IO_RA2_TRIS                 TRISAbits.TRISA2
#define IO_RA2_LAT                  LATAbits.LATA2
#define IO_RA2_PORT                 PORTAbits.RA2
#define IO_RA2_WPU                  WPUAbits.WPUA2
#define IO_RA2_OD                   ODCONAbits.ODCA2
#define IO_RA2_ANS                  ANSELAbits.ANSA2
#define IO_RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_RA2_GetValue()           PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_RA2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_RA2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_RA2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_RA2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set channel_ANC0 aliases
#define channel_ANC0_TRIS                 TRISCbits.TRISC0
#define channel_ANC0_LAT                  LATCbits.LATC0
#define channel_ANC0_PORT                 PORTCbits.RC0
#define channel_ANC0_WPU                  WPUCbits.WPUC0
#define channel_ANC0_OD                   ODCONCbits.ODCC0
#define channel_ANC0_ANS                  ANSELCbits.ANSC0
#define channel_ANC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define channel_ANC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define channel_ANC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define channel_ANC0_GetValue()           PORTCbits.RC0
#define channel_ANC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define channel_ANC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define channel_ANC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define channel_ANC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define channel_ANC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define channel_ANC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define channel_ANC0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define channel_ANC0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set channel_ANC1 aliases
#define channel_ANC1_TRIS                 TRISCbits.TRISC1
#define channel_ANC1_LAT                  LATCbits.LATC1
#define channel_ANC1_PORT                 PORTCbits.RC1
#define channel_ANC1_WPU                  WPUCbits.WPUC1
#define channel_ANC1_OD                   ODCONCbits.ODCC1
#define channel_ANC1_ANS                  ANSELCbits.ANSC1
#define channel_ANC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define channel_ANC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define channel_ANC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define channel_ANC1_GetValue()           PORTCbits.RC1
#define channel_ANC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define channel_ANC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define channel_ANC1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define channel_ANC1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define channel_ANC1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define channel_ANC1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define channel_ANC1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define channel_ANC1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_WPU                  WPUCbits.WPUC2
#define IO_RC2_OD                   ODCONCbits.ODCC2
#define IO_RC2_ANS                  ANSELCbits.ANSC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISCbits.TRISC4
#define SCL1_LAT                  LATCbits.LATC4
#define SCL1_PORT                 PORTCbits.RC4
#define SCL1_WPU                  WPUCbits.WPUC4
#define SCL1_OD                   ODCONCbits.ODCC4
#define SCL1_ANS                  ANSELCbits.ANSC4
#define SCL1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SCL1_GetValue()           PORTCbits.RC4
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISCbits.TRISC5
#define SDA1_LAT                  LATCbits.LATC5
#define SDA1_PORT                 PORTCbits.RC5
#define SDA1_WPU                  WPUCbits.WPUC5
#define SDA1_OD                   ODCONCbits.ODCC5
#define SDA1_ANS                  ANSELCbits.ANSC5
#define SDA1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDA1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDA1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDA1_GetValue()           PORTCbits.RC5
#define SDA1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/