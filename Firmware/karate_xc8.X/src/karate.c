/** INCLUDES *******************************************************/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include <USB/usb_common.h>
#include <USB/usb_device.h>
#include <USB/usb_device_cdc.h>

#include <system_config.h>
#include <tlc5947.h>
#include <comm.h>

/** I N C L U D E S **********************************************************/


/** V A R I A B L E S ********************************************************/
char USB_In_Buffer[64];
char USB_Out_Buffer[64];

uint16_t led_count = 0;
uint8_t  old_sw2;
uint8_t  green_led_counter;
uint8_t  pattern_number;
uint8_t  pic18_rev;
uint16_t pic18_devid;
__EEPROM_DATA(FW_VERSION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
volatile unsigned char* T3GCON_R  = (unsigned char*) 0xFB4;
volatile unsigned char* OSCCON2_R = (unsigned char*) 0xFD2;
volatile unsigned char* ACTCON_R  = (unsigned char*) 0xFB5;
volatile unsigned char* ANSELC_R  = (unsigned char*) 0xF5D;
volatile unsigned char* ANSELA_R  = (unsigned char*) 0xF5B;
volatile unsigned char* IOCB_R    = (unsigned char*) 0xF86;


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void readDeviceID(void);
void InitializeSystem(void);
void ProcessIO(void);
bool SwitchIsPressed(void);
void BlinkUSBStatus(void);
bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size);

/** I N T E R R U P T S ******************************************************/
void interrupt HighPriorityISRCode()
{
  if (PIR2bits.TMR3IF) {
    // preload timer3
    TMR3H = tmr3h_cal;
    TMR3L = tmr3l_cal;

    // Always Latch... only skip if forbidden (count-channels..)
    if (tlc_request >= 0) {
      tlc5947_latch();

      // skip while updating...
      if (tlc_request == 1) {
        tlc5947_update();
      }
    }
    // clear Flag
    PIR2bits.TMR3IF = 0;
  }
}

void interrupt low_priority LowPriorityISRCode()
{
  if (PIR1bits.TMR2IF) {
    // clear Flag
    PIR1bits.TMR2IF = 0;
  }
}

void main(void)
{
  InitializeSystem();

  while(1) {
    if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE)) {
      USBDeviceAttach();
    }
 
    ProcessIO();
  }//end while
}//end main


void InitializeSystem(void)
{
  mInitUnusedPins();
  mInitAllLEDs();

  readDeviceID();  
  
  // device specific initializsation
  if (pic18_devid  == DEVID_PIC18F45K50) {
    OSCTUNE = 0x80; //3X PLL ratio mode selected
    OSCCON = 0x70;  //Switch to 16MHz HFINTOSC
    *OSCCON2_R = 0x10; //Enable PLL, SOSC, PRI OSC drivers turned off
    while((*OSCCON2_R & 0x80) != 0x80);   //Wait for PLL lock
    *ACTCON_R = 0x90;  //Enable active clock tuning for USB operation
    *ANSELC_R = 0;
    *ANSELA_R = 0;     // disable AD
    *IOCB_R   = 0x10;  // Enable RB4 as interrupts-source
  } else {
    ADCON1 = 0x0F;
  }

  DDR_BOOT           = INPUT_PIN;
  DDR_IR             = INPUT_PIN;
  DDR_PWM_READBACK   = INPUT_PIN;
  tris_usb_bus_sense = INPUT_PIN;

  // Init the TLC-Chip
  if (pic18_devid  == DEVID_PIC18F45K50) {
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);  // Init the MSSP-Module
  } else {
    SSPSTAT          = 0x40;
    SSPCON1          = 0x22;
  }
  TRISBbits.TRISB1 = 0;  //SCK
  TRISBbits.TRISB0 = 1;  //MISO
  TRISCbits.TRISC7 = 0;  //MOSI
  mInitTLC5947();
  
  tlc5947_count_channels();               // count channels
 
  // Set up Timer3
  if (pic18_devid  != DEVID_PIC18F4550) {
    T3CON           = 0x77;  // 1/8 Prescaler, FOSC, Enabled
    *T3GCON_R       = 0x73;  // Set GateControll
  } else {
    T3CON           = 0xD1;  //
  }
  IPR2bits.TMR3IP = 1;	   // Make it high-priority
  tlc5947_pwm_readback();  // read PWM Frequency
  PIE2            = 0x02;  // Enable Timer3 Interrupt
    
  tmr3h_cal = (uint8_t)((tlc_pwm_readback_value >> 8 & 0xFF)^0xFF);
  tmr3l_cal = (uint8_t)((tlc_pwm_readback_value      & 0xFF)^0xFF);
  
  // Open the A-D-Converter, only AN0, No Interrupts, select CH0
  //OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0 & ADC_REF_VDD_VREFMINUS & ADC_INT_OFF, ADC_1ANA); //XXX reference selection does _NOT_ work
  ADCON0 = 0x01;
  ADCON1 = 0x0E;
  ADCON2 = 0xBE;

  // Disable other Interrupts
  INTCONbits.INT0IE = 0;   // May be used for IR Decoding

  // Set up Timer2
  T2CON           = 0xFF; // Configure Timer2: 1/16-Prescaler, 1/16-Postscaler, Enabled -> 1Tick equals 21.33ns
  PR2             = 234;  // Will create a 200Hz Interrupt
  PIE1bits.TMR2IE = 0;    // Timer2 Interrupt
  IPR1bits.TMR2IP = 0;    // Timer2 Priority

  USBRegisterFix();   // make pointers to SFR point to the correct registers, based on the device-id
  USBDeviceInit();    //usb_device.c.  Initializes USB module SFRs and firmware variables to known states.
  
  // enable global interrups
  RCONbits.IPEN   = 1;     // Enable Interrupt Priority
  INTCONbits.GIEL = 1;     // LowPriority Interrupts
  INTCONbits.GIEH = 1;     // HighPriority Interrupts  
}//end InitializeSystem

void readDeviceID(void)
{    
  uint8_t devID1, devID2;

  TBLPTRU = 0x3F;
  TBLPTRH = 0xFF;
  TBLPTRL = 0xFE;
  asm( "TBLRD" );
  devID1 = TABLAT;

  TBLPTRL = 0xFF;
  asm( "TBLRD" );
  devID2 = TABLAT;
  
  pic18_devid =  ((uint16_t)devID2 << 3);
  pic18_devid += ((devID1 && 0xE0) >> 5);
} //end readDeviceID(void)


bool SwitchIsPressed(void)
{
  if(sw2 != old_sw2) {
    old_sw2 = sw2;
    if(sw2 == 0) {
      return true;
    }
  }
  return false;
}//end SwitchIsPressed(void))


/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{
  unsigned char x;
 
  // do usb-related stuff
  USBDeviceTasks();
  
  //Set the red LED
  BlinkUSBStatus();

  // reset the green LED
  if (green_led_counter > 0) {
    green_led_counter--;
  } else {     
    mLED_2_Off();
  }

  // check for switch-input
  if (SwitchIsPressed()) {
    pattern_number++;
    if (pattern_number > 6) {
      pattern_number = 0;
    }   

    tlc_request = 0;
    for (x=0; x < tlc_nchannels; x+=3) {
      tlc5947_setChannel(x+0, test_pattern[0 + pattern_number*3]);
      tlc5947_setChannel(x+1, test_pattern[1 + pattern_number*3]);
      tlc5947_setChannel(x+2, test_pattern[2 + pattern_number*3]);
    }
    tlc_request = 1;

    // make green LED blink once..
    mLED_2_On();
    green_led_counter = 255;
  }

  // User Application USB tasks
  if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
  
  // communications-stuff
  ProcessCDC();
  CDCTxService();
} //end ProcessIO

void BlinkUSBStatus(void)
{
  if(led_count-- == 0) {
   led_count = 10000U;
    if ((USBDeviceState == CONFIGURED_STATE) & (USBSuspendControl != 1)) {
      mLED_1_Toggle();
    } else {
      mLED_1_Off();
    }
  }
}//end BlinkUSBStatus

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (int) event )
    {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the 
             * demo code. */
            CDCInitEP();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}




/** EOF main.c *************************************************/

