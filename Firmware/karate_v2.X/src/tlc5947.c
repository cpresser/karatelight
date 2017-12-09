#include <p18cxxx.h>
#include <timers.h>
#include <spi.h>
#include <delays.h>

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "Compiler.h"

#include "tlc5947.h"
#include "comm.h"
#include "gamma.h"

#define TLC_LATCH_DELAY  40

#define TLC_PWM_READBACK_PERIODS 8 // gives about 100Hz Refreshrate

#pragma romdata
ROM unsigned char test_pattern[3*7]= {
  0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00,
  0xFF, 0xFF, 0xFF
};


#pragma udata
unsigned char tlc_memory[72] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
}; // 576 bits == 144 nibbles

unsigned char tlc_nbytes = 72;
unsigned char tlc_nchannels = 48;
char tlc_request = 0;
/*
 * tlc_request < 0       Disable all updates
 * tlc_request = 0       Latch data, but dont send SPI-Data
 * tlc_request = 1       Latch Data & send SPI
 */

unsigned int  tlc_pwm_readback_value = 0;
unsigned char tmr3l_cal = 0;
unsigned char tmr3h_cal = 0;
unsigned char pwr_delay = 0;

#pragma code
void tlc5947_setChannel(unsigned char ch, unsigned char val)
{
  unsigned char pos;
//  unsigned char x;
  unsigned int  col;

  // there are 24/48 sub-channel
  if (ch >= tlc_nchannels) return;

  col = ~gamma_lookup(val);

  // remap channels if in 16-channel-mode
  if (tlc_nchannels == 48) {
    if (ch < 24) {
      ch+=24;
    } else {
      ch-=24;
    }
  }

  pos = ch * 3; // in nibbles
//  x = pos / 2;

  // write first nibble!
  if (pos & 0x01) {
    tlc_memory[(pos/2)] &= 0xF0;  // clear lower nibble
    tlc_memory[(pos/2)] |= ((col & 0xF00) >> 8);
  } else {
    tlc_memory[(pos/2)] &= 0x0F;  // clear upper nibble
    tlc_memory[(pos/2)] |= ((col & 0xF00) >> 4);
  }

  pos++; // write second nibble!
  if (pos & 0x01) {
    tlc_memory[(pos/2)] &= 0xF0;  // clear lower nibble
    tlc_memory[(pos/2)] |= ((col & 0x0F0) >> 4);
  } else {
    tlc_memory[(pos/2)] &= 0x0F;  // clear upper nibble
    tlc_memory[(pos/2)] |= (col & 0x0F0);
  }

  pos++; // write third nibble!
  if (pos & 0x01) {
    tlc_memory[(pos/2)] &= 0xF0;  // clear lower nibble
    tlc_memory[(pos/2)] |= (col & 0x00F);
  } else {
    tlc_memory[(pos/2)] &= 0x0F;  // clear upper nibble
    tlc_memory[(pos/2)] |= ((col & 0x00F) << 4);
  }
}

void tlc5947_count_channels(void)
{
  unsigned char x;
  unsigned char r;

  tlc_request = -1; //disable updates

  // set default value
  tlc_nbytes = 72;

  // input test-bytes
  WriteSPI(tcl5947_testbyte0);
  WriteSPI(tcl5947_testbyte1);

  // start counting channels...
  for (x = 1; x < 255; x++) {
    WriteSPI (0);
    if ((SSPBUF == tcl5947_testbyte1) && (r == tcl5947_testbyte0)) {
      tlc_nbytes = x;
      break;
    }
    r = SSPBUF;
  }
  tlc5947_update();
  tlc_nchannels = tlc_nbytes * 2 / 3;
  tlc_request   = 0; //enable updates again
}

void tlc5947_pwm_readback(void)
{
  unsigned char i;

  //disable updates
  tlc_request    = -1;

  // Set a Pwm-Duty
  tlc5947_setChannel(23, 190);    // Channel 23 is the 'readback' channel
  tlc5947_update();
  tlc5947_latch();

  INTCONbits.IOCIF = 0; // clear Flag

  i = 0;
  while ( 1 ) {
    if (INTCONbits.IOCIF) {
      Delay10TCYx(2);     // denoise...
      if (PIN_PWM_READBACK == 0) {  // negative edge...
        if (i == 0) {
          TMR3H = 0x00;  // Clear Timer3
          TMR3L = 0x00;
        }
        if (i == TLC_PWM_READBACK_PERIODS) {
          break;
        }
        i++;
      }
      INTCONbits.IOCIF = 0;
    }
  }
  // read Timer3
  tlc_pwm_readback_value =  TMR3L;
  tlc_pwm_readback_value += 256 * TMR3H;

  pwr_delay =  (tlc_pwm_readback_value - (2 * TLC_LATCH_DELAY)) / 2 / 100; // Two Factor-100 Delays


  // set it to black again...
  tlc5947_setChannel(23, 0);
  tlc5947_update();
  tlc5947_latch();

  //enable updates again
  tlc_request = 0;
}

void tlc5947_update(void)
{
  unsigned char x;

  for (x = 0; x < tlc_nbytes; x++) {
    WriteSPI (tlc_memory[x]);
  }
  tlc_request = 0;
}

void tlc5947_latch(void)
{
  LED_POWER_Off(); // Force Gates to zero...

  Delay100TCYx (pwr_delay);

  mTLC5947_B_On();

  mTLC5947_L_On();
  Delay10TCYx(TLC_LATCH_DELAY);
  mTLC5947_L_Off();
  Delay10TCYx(TLC_LATCH_DELAY);
  mTLC5947_B_Off();

  Delay100TCYx(pwr_delay);
  LED_POWER_On(); // Power the Gates...
}