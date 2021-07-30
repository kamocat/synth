#include "fm.h"
#include "table.hpp"

SineTable f = SineTable();
uint8_t p[2];

void init_fm(void){
  for(int i=0; i<2; ++i){
    p[i] = 0;
  }
}

int8_t fm(uint8_t rate, uint8_t level, uint8_t pitch){
  p[0] += rate;
  p[1] += pitch; // Carrier frequency
  int16_t v = f.lookup(p[0]);
  v *= level;
  v /= 256;
  v += p[1];
  return f.lookup(v);
}
