#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "HardwareProfile.h"
#include <usb/usb_pic18_local.h>

volatile near unsigned char* U1ADDR_R  = &UADDR;
volatile near unsigned char* U1IE_R    = &UIE;
volatile near unsigned char* U1IR_R    = &UIR;
volatile near unsigned char* U1EIR_R   = &UEIR;
volatile near unsigned char* U1EIE_R   = &UEIE;
volatile near unsigned char* U1CON_R   = &UCON;
volatile near unsigned char* U1EP0_R   = &UEP0;
volatile near unsigned char* U1EP1_R   = &UEP1;
volatile near unsigned char* U1CNFG1_R = &UCFG;
volatile near unsigned char* U1STAT_R  = &USTAT;