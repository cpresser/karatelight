/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        io_cfg.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
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
 * Rawin Rojvanit       11/19/04     Original.
 ********************************************************************/

/******************************************************************************
 * -io_cfg.h-
 * I/O Configuration File
 * The purpose of this file is to provide a mapping mechanism between
 * pin functions and pin assignments. This provides a layer of abstraction
 * for the firmware code and eases the migration process from one target
 * board design to another.
 *
 *****************************************************************************/

#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/
#include "usbcfg.h"

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

/** U S B ***********************************************************/
#define tris_self_power     TRISAbits.TRISA2    // Input
#if defined(USE_SELF_POWER_SENSE_IO)
	#define self_power          PORTAbits.RA2
#else
	#define self_power          1
#endif

#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC6    // Input
#if defined(USE_USB_BUS_SENSE_IO)
	#define USB_BUS_SENSE       PORTCbits.RC6
#else
	#define USB_BUS_SENSE       1
#endif


/** L E D ***********************************************************/
#define mInitAllLEDs()      LATC &= 0xF9; TRISC &= 0xF9;

#define mLED_1              LATCbits.LATC1
#define mLED_2              LATCbits.LATC2

#define mGetLED_1()         mLED_1
#define mGetLED_2()         mLED_2

#define mLED_1_On()         mLED_1 = 1;
#define mLED_2_On()         mLED_2 = 1;

#define mLED_1_Off()        mLED_1 = 0;
#define mLED_2_Off()        mLED_2 = 0;

#define mLED_1_Toggle()     mLED_1 = !mLED_1;
#define mLED_2_Toggle()     mLED_2 = !mLED_2;


#define TLC5947_LE			LATBbits.LATB3
#define TLC5947_BL			LATCbits.LATC0
#define LED_POWER			LATBbits.LATB5
#define mInitTLC5947()		TRISBbits.TRISB3=0; TRISCbits.TRISC0=0; TRISBbits.TRISB5=0; TLC5947_LE=0; TLC5947_BL=1; LED_POWER=0; 

#define	mTLC5947_L_On()		TLC5947_LE = 1;
#define	mTLC5947_L_Off()	TLC5947_LE = 0;

#define	mTLC5947_B_On()		TLC5947_BL = 1;
#define	mTLC5947_B_Off()	TLC5947_BL = 0;

#define	LED_POWER_On()		LED_POWER = 0;
#define	LED_POWER_Off()		LED_POWER = 1;


/** IR PINS ***************************************************/
#define PIN_IR				PORTBbits.RB2
#define DDR_IR				DDRBbits.RB2

#define PIN_BOOT			PORTAbits.RA1
#define DDR_BOOT			DDRAbits.RA1
	
#endif //IO_CFG_H
