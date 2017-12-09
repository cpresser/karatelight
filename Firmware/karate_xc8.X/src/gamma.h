#ifndef _gamma_h_
#define _gamma_h_

extern const uint16_t gamma_table[256];

uint16_t gamma_lookup(uint8_t c);

#endif