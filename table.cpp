#include "table.hpp"

SineTable::SineTable(){
  len = 65;
  const int8_t step = 3;
  const int8_t bits = 2; // Bit space of step
  const int8_t pad = 8 - bits; // Extra padding for better precision
  int16_t x = 127<<pad;
  int16_t y = 0;
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
  if(index > 0x40)
    val = -data[0x7F - index]; // Odd symmetry around pi/2
  else
    val = data[index];
  return val;
}





