#ifndef HARDWARE_PROFILE_PICDEM_FSUSB_H
#define HARDWARE_PROFILE_PICDEM_FSUSB_H

//#define USE_SELF_POWER_SENSE_IO
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


#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER

/** D E F I N E S ************************************************************/
#define FW_VERSION 0x34
#define DEMO_BOARD KARATE_V3
#define PICDEM_FS_USB
#define CLOCK_FREQ 48000000
#define GetSystemClock() (CLOCK_FREQ)
#define DEVID_PIC18F4550 0x0097

//#define BOOTLOAD_START 0x000f1e       // hid-bootloader
#define BOOTLOAD_START   0x000724       //MCHPUSB_20101215.hex

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

#endif  //HARDWARE_PROFILE_PICDEM_FSUSB_H
