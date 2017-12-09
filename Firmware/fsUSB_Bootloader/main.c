/*********************************************************************
 *
 *                Microchip USB Bootloader Version 1.2+Updates
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 3.11+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 * Rawin Rojvanit       05/14/07    Minor updates.
 ********************************************************************/

/*********************************************************************
IMPORTANT NOTE: This booloader example code is not intended to work
with the PIC18F87J50 Family of microcontrollers.
*********************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "typedefs.h"                        // Required
#include "usb.h"                         // Required
#include "io_cfg.h"                                 // Required

#include "usb_compile_time_validation.h" // Optional

/** C O N F I G U R A T I O N ************************************************/

#pragma config PLLDIV   = 5       // (20 MHz input)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2       // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF

#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 1 		// device operates down to 4.2Volt

/*
BORV1:BORV0 = 11 2.05V
BORV1:BORV0 = 10 2.79V
BORV1:BORV0 = 01 4.33V
BORV1:BORV0 = 00 4.59V
*/

#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768

#pragma config MCLRE    = OFF		// make MCLR an input-pin
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
#pragma config CCP2MX   = OFF
#pragma config STVREN   = ON
#pragma config LVP      = OFF
#pragma config ICPRT    = ON       	// Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set

#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CP2      = OFF
#pragma config CP3      = OFF
#pragma config CPB      = OFF		// Protect Boot-Block
#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRT2     = OFF
#pragma config WRT3     = OFF
#pragma config WRTB     = ON      	// Boot Block Write Protection
#pragma config WRTC     = ON		// Config Write Protection
#pragma config WRTD     = OFF		// Protect the EEProm

#pragma config EBTRB    = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTR2    = OFF
#pragma config EBTR3    = OFF


// EEProm-Stuff
#pragma romdata eedata_scn=0xf00000
rom int eedata_version[1] = {0x10};		// Bootloader Version
#pragma romdata


/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/

/** V E C T O R  R E M A P P I N G *******************************************/

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000008
void _high_ISR (void)
{
    _asm goto RM_HIGH_INTERRUPT_VECTOR _endasm
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000018
void _low_ISR (void)
{
    _asm goto RM_LOW_INTERRUPT_VECTOR _endasm
}

#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code


void BootloadStart(void) {
	ADCON1 |= 0x0F;

	RCONbits.IPEN		= 0;
	INTCONbits.GIEH		= 0;
	INTCONbits.GIEL		= 0;


	mInitTLC5947();
	LED_POWER_Off();
	
    //Bootload Mode
    mInitAllLEDs();
    led_count = 0;				//Initialize blink rate counter
    mInitializeUSBDriver();     // See usbdrv.h
    USBCheckBusStatus();        // Modified to always enable USB module
    while(1)
    {
        USBDriverService();     // See usbdrv.c
        BootService();          // See boot.c
    }//end while
}//end main



/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/
void main(void)
{
    ADCON1 = 0x0F;			//Need to make sure RB4 can be used as a digital input pin

	mInitTLC5947();
	LED_POWER_Off();
	
	DDR_BOOT = 1;

	
/*    //Check Bootload Mode Entry Condition
    EEADR = 0x00;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1; */
    

//	if((EEDATA != 0x00) && (PIN_BOOT == 1)) 		// EEProm is free And Button is _not_ Pressed
	if(PIN_BOOT == 1) 		// Button is _not_ Pressed
	{
	    _asm goto RM_RESET_VECTOR _endasm
	}
	BootloadStart();
}


#pragma code user = RM_RESET_VECTOR

/** EOF main.c ***************************************************************/
