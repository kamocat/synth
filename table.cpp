#include "table.h"
#include "tone.h" // for minsky

SineTable::SineTable(){
  len = 17;
  int8_t step = 8*3;
  int8_t x=120;
  data = new int8_t[len];
  for(uint8_t i = 0; i<len; ++i){
    minsky(&x, data+i, step);
  }
}

SineTable::~SineTable(){
  delete data;
}

int8_t SineTable::lookup(int8_t index){
  if(index<0)
    index = -index; // Odd symmetry
  if(index & 0x40)
    index = 0x40-index; // Even symmetry

  //With symmetry, we have taken care of 2 bits.
  //We still have 4 bits of index left, and 2 bits for interpolation
  uint8_t inter = index & 0x3;
  index >>= 2;
  int8_t val;
  int8_t diff = data[index] - data[index+1];
  switch(inter){ // interpolate
    case 1:
      val = data[index] + diff/4;
      break;
    case 2:
      val = data[index] + diff/2;
      break;
    case 3:
      val = data[index+1] - diff/4;
      break;
    default:
      val = data[index];
  }
  return val;
}





