#include <xc.h>
#include <stdint.h>

#include <system_config.h>
#include <tlc5947.h>
#include <gamma.h>

#define TLC_LATCH_DELAY  40
#define TLC_PWM_READBACK_PERIODS 8 // gives about 100Hz Refreshrate

uint8_t tcl5947_testbyte0 = 0x23;
uint8_t tcl5947_testbyte1 = 0x42;
uint8_t test_pattern[3*7]= {
  0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00,
  0xFF, 0xFF, 0xFF
};

uint8_t tlc_memory[72] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
}; // 576 bits == 144 nibbles

uint8_t tlc_nbytes = 72;
uint8_t tlc_nchannels = 48;
int8_t  tlc_request = 0;

uint16_t tlc_pwm_readback_value = 0;
uint8_t  tmr3l_cal = 0;
uint8_t  tmr3h_cal = 0;
uint16_t pwr_delay = 0;

void tlc5947_setChannel(uint8_t ch, uint8_t val)
{
  uint8_t  pos = 0;
  uint8_t  mpos = 0;
  uint16_t col = 0;

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

  // write first nibble!
  mpos = pos >> 1;
  if (pos & 0x01) {
    tlc_memory[mpos] &= 0xF0;  // clear lower nibble
    tlc_memory[mpos] |= ((col & 0xF00) >> 8);
  } else {
    tlc_memory[mpos] &= 0x0F;  // clear upper nibble
    tlc_memory[mpos] |= ((col & 0xF00) >> 4);
  }

  pos++; // write second nibble!
  mpos = pos >> 1;
  if (pos & 0x01) {
    tlc_memory[mpos] &= 0xF0;  // clear lower nibble
    tlc_memory[mpos] |= ((col & 0x0F0) >> 4);
  } else {
    tlc_memory[mpos] &= 0x0F;  // clear upper nibble
    tlc_memory[mpos] |= (col & 0x0F0);
  }

  pos++; // write third nibble!
  mpos = pos >> 1;
  if (pos & 0x01) {
    tlc_memory[mpos] &= 0xF0;  // clear lower nibble
    tlc_memory[mpos] |= (col & 0x00F);
  } else {
    tlc_memory[mpos] &= 0x0F;  // clear upper nibble
    tlc_memory[mpos] |= ((col & 0x00F) << 4);
  }
  pos++;
}

void tlc5947_count_channels(void)
{
  uint8_t pos, data, old_data;

  tlc_request = -1; //disable updates

  // set default value
  tlc_nbytes = 72;

  // input test-bytes
  WriteSPI(tcl5947_testbyte0);
  WriteSPI(tcl5947_testbyte1);

  // start counting channels...
  for (pos = 1; pos <= 72; pos++) {
    data = ReadSPI();
    if ((data == tcl5947_testbyte1) && (old_data == tcl5947_testbyte0)) {
      tlc_nbytes = pos;
      break;
    }
    old_data = data;
  }
  tlc5947_update();
  tlc_nchannels = tlc_nbytes * 2 / 3;
  tlc_request   = 0; //enable updates again
}

void tlc5947_pwm_readback(void)
{
#ifdef __18F45K50
  #define PMW_RB_IF INTCONbits.IOCIF
#else
  #define PMW_RB_IF INTCONbits.RBIF
#endif
  uint8_t i;

  //disable updates
  tlc_request    = -1;

  // Set a Pwm-Duty
  tlc5947_setChannel(23, 190);    // Channel 23 is the 'readback' channel
  tlc5947_update();
  tlc5947_latch();

  PMW_RB_IF = 0; // clear Flag

  i = 0;
  while ( 1 ) {
    if (PMW_RB_IF) {
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
      PMW_RB_IF = 0;
    }
  }
  // read Timer3
  tlc_pwm_readback_value =  TMR3L;
  tlc_pwm_readback_value += 256 * TMR3H;

  pwr_delay = (tlc_pwm_readback_value - (2 * TLC_LATCH_DELAY)) / 2 / 100; // Two Factor-100 Delays

  // set it to black again...
  tlc5947_setChannel(23, 0);
  tlc5947_update();
  tlc5947_latch();

  //enable updates again
  tlc_request = 0;
}

void tlc5947_update(void)
{
  uint8_t x;

  for (x = 0; x < tlc_nbytes; x++) {
    WriteSPI(tlc_memory[x]);
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