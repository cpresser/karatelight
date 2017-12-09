#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include <system_config.h>
#include <comm.h>
#include <tlc5947.h>
#include <gamma.h>

#include <USB/usb_common.h>
#include <USB/usb_device.h>
#include <USB/usb_device_cdc.h>


uint8_t  CDCBufferOut[CDC_DATA_OUT_EP_SIZE];
uint8_t  CDCBufferIn[CDC_DATA_IN_EP_SIZE];
uint16_t update_count = 0;
uint16_t txmiss_count = 0;

void comm_send_rply(unsigned char cc)
{
  CDCBufferOut[CMD_HD_SYNC]     = CMD_SYNC_RECV;
  CDCBufferOut[CMD_HD_COMMAND]  = cc;
  CDCBufferOut[CMD_HD_LEN]      = 0x00;
  CDCBufferOut[CMD_HD_CHECK]    = CDCBufferOut[CMD_HD_SYNC] ^ CDCBufferOut[CMD_HD_COMMAND] ^ CDCBufferOut[CMD_HD_LEN];

  while (!mUSBUSARTIsTxTrfReady()) CDCTxService(); //wait for the usb

  if(USBUSARTIsTxTrfReady()) {
    putUSBUSART(CDCBufferOut, 4);
  } else {
    txmiss_count++;
  }
}

void comm_send_dat(unsigned char len)
{
  unsigned char i;
  if (len >60) {
    len = 60;
  }

  CDCBufferOut[CMD_HD_SYNC]    = CMD_SYNC_RECV;
  CDCBufferOut[CMD_HD_COMMAND] = CMD_SYS_DATA;
  CDCBufferOut[CMD_HD_LEN]     = len;

  len+=4;
  // calc checksum
  CDCBufferOut[CMD_HD_CHECK] = 0;
  for (i = 0 ; i < len; i++) {
    if (i != CMD_HD_CHECK) {
      CDCBufferOut[CMD_HD_CHECK] ^= CDCBufferOut[i];
    }
  }

  while (!mUSBUSARTIsTxTrfReady()) CDCTxService(); //wait for the usb

  if(USBUSARTIsTxTrfReady()) {
    putUSBUSART(CDCBufferOut, len);
  } else {
    txmiss_count++;
  }
}



void ProcessCDC(void)
{
  unsigned char numBytes, len, cmd, csum;
  unsigned char _x,_c = 0;
  unsigned int  _y = 0;

  unsigned char checksum;
  unsigned char boot_request0 = 0x23;
  unsigned char boot_request1 = 0x42;

  // User Application USB tasks
  if ((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

  // get Buffer
  numBytes = getsUSBUSART(CDCBufferIn, CDC_DATA_IN_EP_SIZE);

  // check input
  if ((numBytes >= CMD_DATA_START) &&  (CDCBufferIn[CMD_HD_SYNC] == CMD_SYNC_SEND)) {
    len  = CDCBufferIn[CMD_HD_LEN];
    cmd  = CDCBufferIn[CMD_HD_COMMAND];
    csum = CDCBufferIn[CMD_HD_CHECK];
    if ((len + CMD_DATA_START) == numBytes) {

      // calculate checksum...
      checksum= CDCBufferIn[CMD_HD_SYNC] ^ CDCBufferIn[CMD_HD_COMMAND];
      for (_x = CMD_HD_LEN; _x < numBytes; _x++) {
        checksum ^= CDCBufferIn[_x];
      }
      if (csum == checksum) {
        mLED_2_On();
        green_led_counter = 128;

        switch (cmd) {
        case CMD_READ_ADC0:
          if (len == 0) {
            ConvertADC();
            while (BusyADC());
            _y = ReadADC();
            CDCBufferOut[CMD_DATA_START + 0] = (unsigned char)(_y & 0xFF);
            CDCBufferOut[CMD_DATA_START + 1] = (unsigned char)(_y>>8 & 0xFF);
            comm_send_dat(2);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_SET_DATA_00:
        case CMD_SET_DATA_01:
          if (len == 32) {
            tlc_request = 0;
            for (_x=0; _x<32; _x++) {
              _c = _x + (cmd - CMD_SET_DATA_00) * 32;
              tlc5947_setChannel(_c, CDCBufferIn[CMD_DATA_START + _x]);
            }
            tlc_request = 1;
            update_count++;

            comm_send_rply(CMD_SYS_ACK);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_SET_TLC_DATA:
          // this is a 'legacy' command
          if (len == tlc_nchannels) {
            tlc_request = 0;
            for (_x = 0; _x < tlc_nchannels; _x++) {
              tlc5947_setChannel(_x, CDCBufferIn[CMD_DATA_START + _x]);
            }
            tlc_request = 1;
            update_count++;
            comm_send_rply(CMD_SYS_ACK);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_SET_TLC_CHANNEL:
          // this is a 'legacy' command
          if (len == 2) {
            tlc_request = 0;
            tlc5947_setChannel(CDCBufferIn[CMD_DATA_START], CDCBufferIn[CMD_DATA_START + 1]);
            tlc_request = 1;
            comm_send_rply(CMD_SYS_ACK);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;	

        case CMD_GET_TLC_CHANNELS:
          // this is a 'legacy' command
          if (len == 0) {
            tlc5947_count_channels();
            CDCBufferOut[CMD_DATA_START + 0] = tlc_nbytes;
            comm_send_dat(1);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;
            
        case CMD_GET_N_CHANNELS:
          if (len == 0) {
            tlc5947_count_channels();
            CDCBufferOut[CMD_DATA_START + 0] = tlc_nchannels;
            CDCBufferOut[CMD_DATA_START + 1] = 0;
            comm_send_dat(2);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_GET_TLC_PWM_VALUE:
          if (len == 0) {
            tlc5947_pwm_readback();
            CDCBufferOut[CMD_DATA_START + 0] = (unsigned char)(tlc_pwm_readback_value & 0xFF);
            CDCBufferOut[CMD_DATA_START + 1] = (unsigned char)(tlc_pwm_readback_value>>8 & 0xFF);
            comm_send_dat(2);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_SET_TLC_PWM_VALUE:
          if (len == 2) {
            tmr3l_cal = CDCBufferIn[CMD_DATA_START + 0]^0xFF; // XOR-Invert
            tmr3h_cal = CDCBufferIn[CMD_DATA_START + 1]^0xFF;
            comm_send_rply(CMD_SYS_ACK);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_READ_EEPROM:
          if (len == 1) {
            Busy_eep();
            CDCBufferOut[CMD_DATA_START] = Read_b_eep(CDCBufferIn[CMD_DATA_START]);
            comm_send_dat(1);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_WRITE_EEPROM:
          if (len == 2) {
            Busy_eep();
            Write_b_eep(CDCBufferIn[CMD_DATA_START], CDCBufferIn[CMD_DATA_START+1]);
            comm_send_rply(CMD_SYS_ACK);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_GET_VERSION:
          if (len == 0) {
            CDCBufferOut[CMD_DATA_START] = FW_VERSION;
            comm_send_dat(1);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_GET_HARDWARE:
          if (len == 0) {
            CDCBufferOut[CMD_DATA_START] = HW_ID_KARATE;
            comm_send_dat(1);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_BOOT_REQUEST:
          if (len == 0) {
            CDCBufferOut[CMD_DATA_START + 0] = boot_request0;
            CDCBufferOut[CMD_DATA_START + 1] = boot_request1;
            comm_send_dat(2);
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;

        case CMD_BOOT_START:
          if (len == 2) {
            if ((CDCBufferIn[CMD_DATA_START] == boot_request0) && (CDCBufferIn[CMD_DATA_START + 1] == boot_request1)) {
              INTCONbits.GIE = 0; // shut down global interrupts
              USBSoftDetach();
              USBDeviceTasks();
              Delay10TCYx(18); // 15ms
              if (pic18_devid  != DEVID_PIC18F4550) {
                asm(BOOTLOAD_START_K);
              } else {
                asm(BOOTLOAD_START);  
              }
            } else {
              // request did not match..
              comm_send_rply(CMD_SYS_NACK);
            }
          } else {
            comm_send_rply(CMD_SYS_NACK_LENGTH);
          }
          break;


        default:
          comm_send_rply(CMD_SYS_NIMP);
          break;
        }
      } else {
        // checksum Failure
        comm_send_rply(CMD_SYS_NACK_CHECK);
      }
    } else {
      // numbers of bytes received dont agree with command length
      comm_send_rply(CMD_SYS_NACK_LENGTH);
    }

  } else {
    // else: less than 4 bytes received. discard data.
    len = 0;
  }
} //end ProcessIO
