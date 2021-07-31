#include "table.hpp"

SineTable::SineTable(){
  len = 64;
  const int8_t step = 3;
  const int8_t bits = 2; // Bit space of step
  const int8_t pad = 8 - bits; // Extra padding for better precision
  int16_t x = 127<<pad;
  int16_t y = 5<<pad; // Slight phase advance to fix wave symmetry
  data = new int8_t[len];
  for(uint8_t i = 0; i<len; ++i){
    y += (x*step)>>7;
    x -= (y*step)>>7;
    data[i] = x>>pad;
  }
}

SineTable::~SineTable(){
  delete data;
  len = 0;
}

int8_t SineTable::lookup(int8_t index){
  int8_t val;
  if(index<0)
    index = ~index; // Even symmetry around 0
  if(index >= 0x40)
    val = -data[0x80 - index]; // Odd symmetry around pi/2
  else
    val = data[index];
  return val;
}

Envelope::Envelope(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release){
  state = idle;
  time = 0;
  // Attack slopes from 0 to full value
  if(attack > 0){
    a = limit / attack; 
  } else {
    a = limit;
  }
  // Sustain is the level to hold at
  s = sustain; 
  // Decay slopes from full value to sustain level
  d = 256 - sustain;
  d <<= 7;
  if(decay > 0) // Catch divide-by-zero
    d /= decay;
  // Release slopes from sustain down to zero
    r = s;
    r <<= 7;
  if(release > 0) // Catch divide-by-zero
    r /= release;
  /* Divide-by-zero issue:
  ** These should be integer divides, which have no issue with zero-division.
  ** However, they are compiling as floating-point division, and throwing
  ** exceptions when the divisor is zero. So this is a workaround.
  */
}

uint8_t Envelope::update(uint8_t dt, bool pressed){
  uint8_t tmp;
  switch(state){
    case at:
      time += dt * a;
      if( time >= 0 ){
        return time >> 7;
      } else {
        state = dec;
        time = limit - 1;
        return 255;
      }
    case dec:
      time -= dt * d;
      tmp = time >> 7;
      if( tmp > s )
        return tmp;
      else
        state = sus;
    case sus:
      if( pressed )
        return s;
      else{
        time = s << 7;
        state = rel;
      }
    case rel:
      time -= dt * r;
      if( time > 0){
        if(pressed)
          state = at;
        return time>>7;
      }else
        state = idle;
    default:
      if(pressed)
        state = at;
      return 0;
  }
}

uint8_t Logvelope::log2(uint8_t x){
  uint8_t tmp = x;
  int8_t mag = 0;
  for(; tmp>>=1; ++mag);
  tmp = mag;
  mag -= 5;
  if(mag > 0)
    x >>= mag;
  else
    x <<= -mag;
  x &= 0x1F;
  x |= tmp<<5;
  return x;
}

uint8_t Logvelope::exp2(uint8_t x){
  /* Exponential mapping of 8-bit integer.
  ** Because log2(8) is 3, we are treating this as a 3.5 fixed-point input
  ** Where the integer portion determines the power, and the fractional
  ** portion remains linear
  */
  int8_t mag = x>>5; // The first 3 bits determine gross magnitude
  uint8_t tmp = x & 0x3F | 0x20; // Make sure leading bit is 1
  mag -= 5;
  if(mag>0)
    tmp <<= mag;
  else
    tmp >>= -mag;
  return tmp;
}

uint8_t Logvelope::update(uint8_t dt, bool pressed){
  uint8_t ret = Envelope::update(dt, pressed);
  return exp2(ret);
}
