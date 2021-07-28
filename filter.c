#include "filter.h"

int8_t interpolate(int8_t a, int8_t b, uint8_t mix){
  int16_t c = mix;
  c *= (b-a);
  c>>=8;
  return (a + c);
}

int8_t bandpass(int8_t * y, int8_t x, uint8_t cl, uint8_t ch){
  int8_t tmp = *y;
  int16_t c = cl;
  c *= (x-tmp);
  c>>=8;
  *y = c;
  c = ch;
  c *= tmp;
  c>>=8;
  tmp = c;
  return (*y-tmp);
}

