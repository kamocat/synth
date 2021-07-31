#include <cmath>
#include <fstream>
#include <iostream>
#include "tone.h"
#include "audio.hpp"

int test_mul8(int8_t a, int8_t b, int8_t y){
  int tmp = mul8(a,b);
  bool pass = y==tmp;
  std::cout << int(a)<< "*" << int(b)<< "=" << tmp 
    << "..."<<(pass?"PASS":"FAIL")<<std::endl;
  return !pass;
}

int main()
{
  test_mul8(127,127,126);
  test_mul8(-127,-127,126);
  test_mul8(127,0,0);
  test_mul8(64,2,1);

  // Minsky circle doesn't need testing at this point.
  // We know it works for constant dt, but not for variable dt
}
