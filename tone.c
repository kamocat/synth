#include "tone.h"

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
