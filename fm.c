#include "synth.h"
#include "fm.h"

static int8_t p[4];

void init_fm(void){
  for(int i=0; i<2; ++i){
    p[2*i]=100;
    p[2*i+1] = 0;
  }
}

int8_t fm(uint8_t rate, uint8_t level){
  int16_t v = minsky(p, p+1, rate);
  v *= level;
  v /= 256;
  v += 2;
  return minsky(p+2, p+3, 2);
}
