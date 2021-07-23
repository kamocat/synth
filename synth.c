#include "synth.h"
#define N 9

int8_t amplitudes[N]  = { 5, 15, 25, 15, 10, 5, 1, 1,1 };
int8_t frequencies[N] = { 2,3,4,5,6,7,8,9,10 };
// Phase adjustments can be made by changing the initialization
int8_t p[N*2] = {0, 100, 100, 100, 100, 100,   0,  0, 100,
                 100,   0,   0,   0,   0,   0,   100,100,   0};

void synth_init(void){
}

int8_t synth(void){
  int16_t sum = 0;
  int16_t m;
  for(int i=0; i<N; ++i){
    m = triangle(p+i,p+i+N,frequencies[i]);
    m *= amplitudes[i];
    sum += m;
  }
  return sum>>7;
}

int8_t minsky(int8_t *x, int8_t *y, int8_t dt){
  *y += mul8(*x, dt);
  *x -= mul8(*y, dt);
  return *x;
}

int8_t triangle(int8_t *x, int8_t *y, int8_t dt){
  if(*x < 0)
    --*y;
  else
    ++*y;
  if(*y < 0)
    ++*x;
  else
    --*x;
  return *x;
}

int8_t mul8(int8_t a, int8_t b){
  int16_t tmp = a;
  tmp *= b;
  return tmp>>7;
}
