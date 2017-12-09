#ifndef _tlc5947_h_
#define _tlc5947_h_

extern uint16_t pic18_devid;

extern uint8_t test_pattern[3*7];
extern uint8_t tlc_memory[72];
extern uint8_t tlc_nbytes;
extern uint8_t tlc_nchannels;

extern uint16_t tlc_pwm_readback_value;
extern uint8_t  tmr3l_cal;
extern uint8_t  tmr3h_cal;
extern int8_t   tlc_request;
/*
 * tlc_request < 0       Disable all updates
 * tlc_request = 0       Latch data, but dont send SPI-Data
 * tlc_request = 1       Latch Data & send SPI
 */


void tlc5947_setChannel(uint8_t c, uint8_t val);
void tlc5947_update(void);
void tlc5947_latch(void);
void tlc5947_count_channels(void);
void tlc5947_pwm_readback(void);

#endif
