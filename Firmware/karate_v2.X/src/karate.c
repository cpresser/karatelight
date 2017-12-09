/** INCLUDES *******************************************************/
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "HardwareProfile.h"

#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "./USB/usb_device.h"
#include "./USB/usb.h"

#include "comm.h"
#include "tlc5947.h"

#include <spi.h>
#include <adc.h>


#pragma romdata eedata_scn=0xf00000
rom int eedata [2] = {
  FW_VERSION, // Firmware Version
  0           // DMX-Offset
};

/** I N C L U D E S **********************************************************/


/** V A R I A B L E S ********************************************************/
#pragma udata
char USB_In_Buffer[64];
char USB_Out_Buffer[64];

BYTE old_sw2;
unsigned char pattern_number;
unsigned char pic18_rev;
unsigned short pic18_devid;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
void ProcessIO(void);
void USBDeviceTasks(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);

/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
#define REMAPPED_RESET_VECTOR_ADDRESS             0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS    0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS     0x1018
#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
#define REMAPPED_RESET_VECTOR_ADDRESS             0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS    0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS     0x818
#else
#define REMAPPED_RESET_VECTOR_ADDRESS             0x00
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS    0x08
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS     0x18
#endif

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void)
{
  _asm goto _startup _endasm
}
#endif

#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)
{
  _asm goto YourHighPriorityISRCode _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void)
{
  _asm goto YourLowPriorityISRCode _endasm
}

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)
{
  _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void)
{
  _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}
#endif    //end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"


//These are your actual interrupt handling routines.
#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()
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

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()
{
  if (PIR1bits.TMR2IF) {
    // clear Flag
    PIR1bits.TMR2IF = 0;
  }
}
#endif




/** DECLARATIONS ***************************************************/
#pragma code

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
  InitializeSystem();

  while(1) {
    if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE)) {
      USBDeviceAttach();
    }

    ProcessIO();
  }//end while
}//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
  unsigned char dev1, dev2;
  memcpypgm2ram((void *)&dev1, (rom void *)0x3FFFFE, 1);
  memcpypgm2ram((void *)&dev2, (rom void *)0x3FFFFF, 1);
  pic18_rev = dev1 & 0x01F;
  pic18_devid = ((unsigned short)dev2 << 3) | (dev1 >> 5);

  // device specific initializsation
  if (pic18_devid == DEVID_PIC18F4550) {
    ADCON1 = 0x0F;
  } else {
    OSCCON           = 0xF8;  // use internal OSC
    ANSELAbits.ANSA1 = 0;     // disable AD
    IOCBbits.IOCB4   = 1;     // Enable RB4 as interrupts-source
  }

#if defined(USE_USB_BUS_SENSE_IO)
  tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
#endif

#if defined(USE_SELF_POWER_SENSE_IO)
  tris_self_power = INPUT_PIN;  // See HardwareProfile.h
#endif

  mInitUnusedPins();
  mInitAllLEDs();

  DDR_BOOT          = INPUT_PIN;
  DDR_IR            = INPUT_PIN;
  DDR_PWM_READBACK  = INPUT_PIN;

  // Init the TLC-Chip
  OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);  // Init the MSSP-Module
  mInitTLC5947();               // configure IO-pins
  tlc5947_count_channels();     // count channels

  // Set up Timer3
  T3CON               = 0xB1; // 1/8 Prescaler, Enabled
  PIE2bits.TMR3IE = 1;     // Enable Timer3 Interrupt
  IPR2bits.TMR3IP = 1;     // Make it high-priority

  tlc5947_pwm_readback();       // read PWM Frequency
  tmr3h_cal = (unsigned char)((tlc_pwm_readback_value>>8 & 0xFF)^0xFF);
  tmr3l_cal = (unsigned char)((tlc_pwm_readback_value    & 0xFF)^0xFF);

  // Open the A-D-Converter, only AN0, No Interrupts, select CH0
  //OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0 & ADC_REF_VDD_VREFMINUS & ADC_INT_OFF, ADC_1ANA); //XXX reference selection does _NOT_ work
  ADCON0 = 0x01;
  ADCON1 = 0x0E;
  ADCON2 = 0xBE;

  // Disable other Interrupts
  INTCONbits.INT0IE = 0;   // May be used for IR Decoding

  // Interrupts for PWM_Readback
  INTCONbits.IOCIE = 0;  // Disable Int

  // Set up Timer2
  T2CON           = 0xFF; // Configure Timer2: 1/16-Prescaler, 1/16-Postscaler, Enabled -> 1Tick equals 21.33ns
  PR2             = 234;  // Will create a 200Hz Interrupt
  PIE1bits.TMR2IE = 0;    // Timer2 Interrupt
  IPR1bits.TMR2IP = 0;    // Timer2 Priority


  USBDeviceInit();    //usb_device.c.  Initializes USB module SFRs and firmware variables to known states.

  // enable global interrups
  RCONbits.IPEN   = 1;     // Enable Interrupt Priority
  INTCONbits.GIEL = 1;     // LowPriority Interrupts
  INTCONbits.GIEH = 1;     // HighPriority Interrupts

}//end InitializeSystem


BOOL Switch2IsPressed(void)
{
  if(sw2 != old_sw2) {
    old_sw2 = sw2;                  // Save new value
    if(sw2 == 0)                    // If pressed
      return TRUE;                // Was pressed
  }//end if
  return FALSE;                       // Was not pressed
}//end Switch2IsPressed


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
  if (Switch2IsPressed()) {
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
    green_led_counter=128;
  }

  // User Application USB tasks
  if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

  // communications-stuff
  ProcessCDC();
  CDCTxService();
}         //end ProcessIO

/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void)
{
  static WORD led_count=0;

  if(led_count == 0)led_count = 10000U;
  led_count--;

  if ((USBDeviceState == CONFIGURED_STATE) & (USBSuspendControl != 1)) {
    if(led_count==0) {
      mLED_1_Toggle();
    }
  } else {
    mLED_1_Off();
  }


}//end BlinkUSBStatus




// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
  //Example power saving code.  Insert appropriate code here for the desired
  //application behavior.  If the microcontroller will be put to sleep, a
  //process similar to that shown below may be used:

  //ConfigureIOPinsForLowPower();
  //SaveStateOfAllInterruptEnableBits();
  //DisableAllInterruptEnableBits();
  //EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();   //should enable at least USBActivityIF as a wake source
  //Sleep();
  //RestoreStateOfAllPreviouslySavedInterruptEnableBits();    //Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
  //RestoreIOPinsToNormal();                                            //Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

  //IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is
  //cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause
  //things to not work as intended.


#if defined(__C30__)
  USBSleepOnSuspend();
#endif
}

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *                       suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *                       mode, the host may wake the device back up by sending non-
 *                       idle state signalling.
 *
 *                       This call back is invoked when a wakeup from USB suspend
 *                       is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
  // If clock switching or other power savings measures were taken when
  // executing the USBCBSuspend() function, now would be a good time to
  // switch back to normal full power run mode conditions.  The host allows
  // a few milliseconds of wakeup time, after which the device must be
  // fully back to normal, and capable of receiving and processing USB
  // packets.  In order to do this, the USB module must receive proper
  // clocking (IE: 48MHz clock must be available to SIE for full speed USB
  // operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
  // No need to clear UIRbits.SOFIF to 0 here.
  // Callback caller is already doing that.

}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
  // No need to clear UEIR to 0 here.
  // Callback caller is already doing that.

  // Typically, user firmware does not need to do anything special
  // if a USB error occurs.  For example, if the host sends an OUT
  // packet to your device, but the packet gets corrupted (ex:
  // because of a bad connection, or the user unplugs the
  // USB cable during the transmission) this will typically set
  // one or more USB error interrupt flags.  Nothing specific
  // needs to be done however, since the SIE will automatically
  // send a "NAK" packet to the host.  In response to this, the
  // host will normally retry to send the packet again, and no
  // data loss occurs.  The system will typically recover
  // automatically, without the need for application firmware
  // intervention.

  // Nevertheless, this callback function is provided, such as
  // for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 *                       firmware must process the request and respond
 *                       appropriately to fulfill the request.  Some of
 *                       the SETUP packets will be for standard
 *                       USB "chapter 9" (as in, fulfilling chapter 9 of
 *                       the official USB specifications) requests, while
 *                       others may be specific to the USB device class
 *                       that is being implemented.  For example, a HID
 *                       class device needs to be able to respond to
 *                       "GET REPORT" type of requests.  This
 *                       is not a standard USB chapter 9 request, and
 *                       therefore not handled by usb_device.c.  Instead
 *                       this request should be handled by class specific
 *                       firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
  USBCheckCDCRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *                       called when a SETUP, bRequest: SET_DESCRIPTOR request
 *                       arrives.  Typically SET_DESCRIPTOR requests are
 *                       not used in most applications, and it is
 *                       optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
  // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 *                       SET_CONFIGURATION (wValue not = 0) request.  This
 *                       callback function should initialize the endpoints
 *                       for the device's usage according to the current
 *                       configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
  CDCInitEP();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 *                       peripheral devices to wake up a host PC (such
 *                       as if it is in a low power suspend to RAM state).
 *                       This can be a very useful feature in some
 *                       USB applications, such as an Infrared remote
 *                       control   receiver.  If a user presses the "power"
 *                       button on a remote control, it is nice that the
 *                       IR receiver can detect this signalling, and then
 *                       send a USB "command" to the PC to wake up.
 *
 *                       The USBCBSendResume() "callback" function is used
 *                       to send this special USB signalling which wakes
 *                       up the PC.  This function may be called by
 *                       application firmware to wake up the PC.  This
 *                       function should only be called when:
 *
 *                       1.  The USB driver used on the host PC supports
 *                            the remote wakeup capability.
 *                       2.  The USB configuration descriptor indicates
 *                            the device is remote wakeup capable in the
 *                            bmAttributes field.
 *                       3.  The USB host PC is currently sleeping,
 *                            and has previously sent your device a SET
 *                            FEATURE setup packet which "armed" the
 *                            remote wakeup capability.
 *
 *                       This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()

 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
  static WORD delay_count;

  USBResumeControl = 1;                // Start RESUME signaling

  delay_count = 1800U;                // Set RESUME line for 1-13 ms
  do {
    delay_count--;
  } while(delay_count);
  USBResumeControl = 0;
}


/*******************************************************************
 * Function:        void USBCBEP0DataReceived(void)
 *
 * PreCondition:    ENABLE_EP0_DATA_RECEIVED_CALLBACK must be
 *                  defined already (in usb_config.h)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called whenever a EP0 data
 *                  packet is received.  This gives the user (and
 *                  thus the various class examples a way to get
 *                  data that is received via the control endpoint.
 *                  This function needs to be used in conjunction
 *                  with the USBCBCheckOtherReq() function since
 *                  the USBCBCheckOtherReq() function is the apps
 *                  method for getting the initial control transfer
 *                  before the data arrives.
 *
 * Note:            None
 *******************************************************************/
#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void)
{
}
#endif

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
  switch(event) {
  case EVENT_CONFIGURED:
    USBCBInitEP();
    break;
  case EVENT_SET_DESCRIPTOR:
    USBCBStdSetDscHandler();
    break;
  case EVENT_EP0_REQUEST:
    USBCBCheckOtherReq();
    break;
  case EVENT_SOF:
    USBCB_SOF_Handler();
    break;
  case EVENT_SUSPEND:
    USBCBSuspend();
    break;
  case EVENT_RESUME:
    USBCBWakeFromSuspend();
    break;
  case EVENT_BUS_ERROR:
    USBCBErrorHandler();
    break;
  case EVENT_TRANSFER:
    Nop();
    break;
  default:
    break;
  }
  return TRUE;
}


/** EOF main.c *************************************************/

