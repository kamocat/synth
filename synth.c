#include "synth.h"
#define N 2

int16_t xp, yp, dt;

void synth_init(void){
  // xp/dt >= 5/2
  xp = 32000;
  yp = 0;
  dt = 30;
}

int16_t synth(void){
  yp += xp / dt;
  xp -= yp / dt;
  return xp;
}

