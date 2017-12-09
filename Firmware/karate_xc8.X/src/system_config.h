#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <usb_config.h>
#include <usb_hal_fixes.h>


#define self_power 1

#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC6    // Input
#if defined(USE_USB_BUS_SENSE_IO)
#define USB_BUS_SENSE       PORTCbits.RC6
#else
#define USB_BUS_SENSE       1
#endif


/** D E F I N E S ************************************************************/
#define FW_VERSION 0x34
#define DEMO_BOARD KARATE_V3
#define PICDEM_FS_USB
#define CLOCK_FREQ 48000000
#define GetSystemClock() (CLOCK_FREQ)
#define DEVID_PIC18F4550  0x0090
#define DEVID_PIC18F45K50 0x02E0

#define BOOTLOAD_START   "goto 0x000724"       // MCHPUSB_20101215.hex
#define BOOTLOAD_START_K "goto 0x00073c"       // 20150309_bootloader_18f45k50.hex

/** U S B - D A T A   L O C A T I O N ****************************************/
#define FIXED_ADDRESS_MEMORY
#define IN_DATA_BUFFER_ADDRESS_TAG      @0x500
#define OUT_DATA_BUFFER_ADDRESS_TAG     @0x540
#define CONTROL_BUFFER_ADDRESS_TAG      @0x580

/** LED ************************************************************/
#define mInitAllLEDs()        LATC &= 0xF9; TRISC &= 0xF9;

#define mLED_1                LATCbits.LATC1
#define mLED_2                LATCbits.LATC2

#define mGetLED_1()           mLED_1
#define mGetLED_2()           mLED_2

#define mLED_1_On()           mLED_1 = 1;
#define mLED_2_On()           mLED_2 = 1;

#define mLED_1_Off()          mLED_1 = 0;
#define mLED_2_Off()          mLED_2 = 0;

#define mLED_1_Toggle()       mLED_1 = !mLED_1;
#define mLED_2_Toggle()       mLED_2 = !mLED_2;

/** TLC5925 PINS ***************************************************/
#define TLC5947_LE            LATBbits.LATB3
#define TLC5947_BL            LATCbits.LATC0
#define LED_POWER             LATBbits.LATB5
#define mInitTLC5947()        TRISBbits.TRISB3=0; TRISCbits.TRISC0=0; TRISBbits.TRISB5=0; TLC5947_LE=0; TLC5947_BL=1; LED_POWER=0;

#define   mTLC5947_L_On()     TLC5947_LE = 1;
#define   mTLC5947_L_Off()    TLC5947_LE = 0;

#define   mTLC5947_B_On()     TLC5947_BL = 1;
#define   mTLC5947_B_Off()    TLC5947_BL = 0;

#define   LED_POWER_On()      LED_POWER = 0;
#define   LED_POWER_Off()     LED_POWER = 1;


/** OTHER PINS ***************************************************/
#define PIN_IR                PORTBbits.RB2
#define DDR_IR                DDRBbits.RB2

#define PIN_BOOT              PORTAbits.RA1
#define sw2                   PORTAbits.RA1
#define DDR_BOOT              DDRAbits.RA1

#define PIN_PWM_READBACK      PORTBbits.RB4
#define DDR_PWM_READBACK      DDRBbits.RB4


/** UNUSED PINS ***********************************************/
// PortA: RA2, RA3, RA4, RA5
// PortB: RB6, RB7
// PortC: none unused
// PortD: all
// PortE: all
#define mInitUnusedPins()     DDRE &= 0x00; DDRD &= 0x00; DDRC &= 0xFF; DDRB &= 0x3F; DDRA &= 0xC3;


/** I/O pin definitions ********************************************/
#define INPUT_PIN  1
#define OUTPUT_PIN 0

/* 
 * RA0 IN  AnalogIN
 * RA1 IN  BootSwitch
 * RA2 NC  -
 * RA3 NC  -
 * RA4 NC  -
 * RA5 NC  -
 * 
 * RB0 IN  TLC_MISO
 * RB1 OUT TLC_SCK
 * RB2 IN  IR_INT
 * RB3 OUT TLC_LATCH
 * RB4 IN  TLC_READBACK
 * RB5 OUT TLC_POWER
 * RB6 NC  -
 * RB7 NC  -
 * 
 * RC0 OUT TLC_BLANK
 * RC1 OUT LED1
 * RC2 OUT LED0
 * RC3 USB VREG
 * RC4 USB USB_D-
 * RC5 USB USB_D+
 * RC6 IN  USB_SENSE
 * RC7 OUT TLC_MOSI
 * 
 * RD0 NC  -
 * RD1 NC  -
 * RD2 NC  -
 * RD3 NC  -
 * RD4 NC  -
 * RD5 NC  -
 * RD6 NC  -
 * RD7 NC  -
 * 
 * RE0 NC  -
 * RE1 NC  -
 * RE2 NC  -
 * RE3 NC  -
 *
 */

#endif  //SYSTEM_CONFIG_H_
