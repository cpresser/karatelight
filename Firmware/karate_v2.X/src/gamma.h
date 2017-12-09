#ifndef _gamma_h_
#define _gamma_h_

extern rom unsigned int gamma_table[256];

int gamma_lookup(unsigned char c);

#endif