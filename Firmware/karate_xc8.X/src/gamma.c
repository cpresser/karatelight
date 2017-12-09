#include <stdint.h>

// Gamma-Table at 2.5
uint16_t gamma_table[256]= {
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0001,0x0001,0x0001,0x0002,0x0002,0x0002,0x0003,0x0003,
  0x0004,0x0005,0x0005,0x0006,0x0007,0x0008,0x0009,0x000A,0x000B,0x000C,0x000E,0x000F,0x0010,0x0012,0x0013,0x0015,
  0x0017,0x0019,0x001B,0x001D,0x001F,0x0021,0x0023,0x0025,0x0028,0x002A,0x002D,0x0030,0x0033,0x0036,0x0039,0x003C,
  0x003F,0x0042,0x0046,0x0049,0x004D,0x0051,0x0055,0x0058,0x005D,0x0061,0x0065,0x0069,0x006E,0x0073,0x0077,0x007C,
  0x0081,0x0086,0x008C,0x0091,0x0096,0x009C,0x00A2,0x00A8,0x00AD,0x00B4,0x00BA,0x00C0,0x00C7,0x00CD,0x00D4,0x00DB,
  0x00E2,0x00E9,0x00F0,0x00F8,0x00FF,0x0107,0x010E,0x0116,0x011E,0x0127,0x012F,0x0138,0x0140,0x0149,0x0152,0x015B,
  0x0164,0x016D,0x0177,0x0181,0x018A,0x0194,0x019E,0x01A9,0x01B3,0x01BE,0x01C8,0x01D3,0x01DE,0x01E9,0x01F4,0x0200,
  0x020C,0x0217,0x0223,0x022F,0x023C,0x0248,0x0254,0x0261,0x026E,0x027B,0x0288,0x0296,0x02A3,0x02B1,0x02BF,0x02CD,
  0x02DB,0x02E9,0x02F8,0x0307,0x0315,0x0325,0x0334,0x0343,0x0353,0x0362,0x0372,0x0382,0x0393,0x03A3,0x03B4,0x03C4,
  0x03D5,0x03E6,0x03F8,0x0409,0x041B,0x042D,0x043F,0x0451,0x0463,0x0476,0x0489,0x049C,0x04AF,0x04C2,0x04D6,0x04E9,
  0x04FD,0x0511,0x0525,0x053A,0x054E,0x0563,0x0578,0x058D,0x05A3,0x05B8,0x05CE,0x05E4,0x05FA,0x0610,0x0627,0x063E,
  0x0655,0x066C,0x0683,0x069B,0x06B2,0x06CA,0x06E2,0x06FB,0x0713,0x072C,0x0745,0x075E,0x0777,0x0791,0x07AA,0x07C4,
  0x07DE,0x07F9,0x0813,0x082E,0x0849,0x0864,0x0880,0x089B,0x08B7,0x08D3,0x08EF,0x090B,0x0928,0x0945,0x0962,0x097F,
  0x099D,0x09BA,0x09D8,0x09F6,0x0A15,0x0A33,0x0A52,0x0A71,0x0A90,0x0AB0,0x0ACF,0x0AEF,0x0B0F,0x0B2F,0x0B50,0x0B71,
  0x0B92,0x0BB3,0x0BD4,0x0BF6,0x0C18,0x0C3A,0x0C5C,0x0C7E,0x0CA1,0x0CC4,0x0CE7,0x0D0B,0x0D2E,0x0D52,0x0D76,0x0D9B,
  0x0DBF,0x0DE4,0x0E09,0x0E2E,0x0E54,0x0E79,0x0E9F,0x0EC5,0x0EEC,0x0F12,0x0F39,0x0F60,0x0F88,0x0FAF,0x0FD7,0x0FFF
};

uint16_t gamma_lookup(uint8_t c)
{
  return gamma_table[c];
}