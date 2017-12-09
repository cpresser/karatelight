#include <xc.h>
#include <stdint.h>
#include <system_config.h>

volatile unsigned char* U1ADDR_R  = &UADDR;
volatile unsigned char* U1IE_R    = &UIE;
volatile unsigned char* U1IR_R    = &UIR;
volatile unsigned char* U1EIR_R   = &UEIR;
volatile unsigned char* U1EIE_R   = &UEIE;
volatile unsigned char* U1CON_R   = &UCON;
volatile unsigned char* U1EP0_R   = &UEP0;
volatile unsigned char* U1EP1_R   = &UEP1;
volatile unsigned char* U1CNFG1_R = &UCFG;
volatile unsigned char* U1STAT_R  = &USTAT;

volatile unsigned char* PIE2_R    = (unsigned char*)0xFA0;
volatile unsigned char* PIR2_R    = (unsigned char*)0xFA1;
volatile unsigned char* PIE3_R    = (unsigned char*)0xFA3;
volatile unsigned char* PIR3_R    = (unsigned char*)0xFA4;

extern uint16_t pic18_devid;

void USBClearUSBInterrupt() {
  if (pic18_devid  == DEVID_PIC18F45K50) {
    *PIR3_R &= 0b11111011;
  } else {
    *PIR2_R &= 0b11011111;
  }
}

void USBDisableInterrupts() {
  if (pic18_devid  == DEVID_PIC18F45K50) {
    *PIE3_R &= 0b11111011;
  } else {
    *PIR2_R &= 0b11011111;
  }
}
void USBRegisterFix() {
  if (pic18_devid  == DEVID_PIC18F45K50) {
    //DS30684A Page 92
    U1ADDR_R  = (unsigned char*)0xF63;
    U1IE_R    = (unsigned char*)0xF64;
    U1IR_R    = (unsigned char*)0xF65;
    U1EIR_R   = (unsigned char*)0xF67;
    U1EIE_R   = (unsigned char*)0xF66;
    U1CON_R   = (unsigned char*)0xF60;
    U1EP0_R   = (unsigned char*)0xF6A;
    U1EP1_R   = (unsigned char*)0xF6B;
    U1CNFG1_R = (unsigned char*)0xF62;
    U1STAT_R  = (unsigned char*)0xF61;
  } else {
    //DS39632E Page 68
    U1ADDR_R  = (unsigned char*)0xF6E;
    U1IE_R    = (unsigned char*)0xF69;
    U1IR_R    = (unsigned char*)0xF68;
    U1EIR_R   = (unsigned char*)0xF6A;
    U1EIE_R   = (unsigned char*)0xF6B;
    U1CON_R   = (unsigned char*)0xF6D;
    U1EP0_R   = (unsigned char*)0xF70;
    U1EP1_R   = (unsigned char*)0xF71;
    U1CNFG1_R = (unsigned char*)0xF6F;
    U1STAT_R  = (unsigned char*)0xF6C;
  }
}