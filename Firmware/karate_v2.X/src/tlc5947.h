#ifndef _tlc5947_h_
#define _tlc5947_h_

#define tcl5947_testbyte0     0x23
#define tcl5947_testbyte1     0x42

extern rom unsigned char test_pattern[3*7];

extern unsigned char tlc_memory[72];
extern unsigned char tlc_nbytes;
extern unsigned char tlc_nchannels;

extern unsigned int  tlc_pwm_readback_value;
extern unsigned char tmr3l_cal;
extern unsigned char tmr3h_cal;
extern char tlc_request;


void tlc5947_setChannel(unsigned char c, unsigned char val);
void tlc5947_update(void);
void tlc5947_latch(void);
void tlc5947_count_channels(void);
void tlc5947_pwm_readback(void);

#endif
