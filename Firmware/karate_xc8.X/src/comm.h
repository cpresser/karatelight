#ifndef _comm_h_
#define _comm_h_

extern uint8_t  CDCBufferOut[CDC_DATA_OUT_EP_SIZE];
extern uint8_t  green_led_counter;
extern uint16_t update_count;


/** C O M M U N I C A T I O N ***************************************/
// address
#define CMD_HD_SYNC             0x00
#define CMD_HD_COMMAND          0x01
#define CMD_HD_CHECK            0x02
#define CMD_HD_LEN              0x03
#define CMD_DATA_START          0x04

// sync words
#define CMD_SYNC_SEND           0xAA
#define CMD_SYNC_RECV           0x55

// commands
#define CMD_SYS_SYNC            0x00
#define CMD_SYS_ACK             0x01
#define CMD_SYS_NACK            0x02
#define CMD_SYS_NIMP            0xFF
#define CMD_SYS_IR              0x10
#define CMD_SYS_DATA            0x20
#define CMD_SYS_NACK_LENGTH     0x03
#define CMD_SYS_NACK_CHECK      0x04

#define CMD_GET_VERSION         0x01
#define CMD_GET_HARDWARE        0x02

#define CMD_SET_TLC_DATA_RAW    0x10
#define CMD_SET_TLC_CHANNEL     0x11
#define CMD_SET_TLC_DATA        0x12
#define CMD_GET_TLC_CHANNELS    0x13

#define CMD_GET_TLC_PWM_VALUE   0x14
#define CMD_SET_TLC_PWM_VALUE   0x15

#define CMD_SET_DATA_00         0x20
#define CMD_SET_DATA_01         0x21

#define CMD_GET_N_CHANNELS      0x30

#define CMD_READ_ADC0           0x40

#define CMD_READ_EEPROM         0x50
#define CMD_WRITE_EEPROM        0x51

#define CMD_BOOT_REQUEST        0x80
#define CMD_BOOT_START          0x81

#define HW_ID_KARATE            0x01
#define HW_ID_USB2DMX           0x02

void ProcessCDC(void);

#endif
