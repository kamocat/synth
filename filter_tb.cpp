#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "filter.h"
#include "audio.hpp"

int test_interp(int a, int b, unsigned int c, int y){
  int tmp = interpolate(a,b,c);
  bool pass = y==tmp;
  std::cout << a<< ".." << b<< "@" << c << "=" << tmp 
    << ":\t"<<(pass?"PASS":"FAIL")<<std::endl;
  return !pass;
}

int main()
{
  test_interp(0,100,128,50);
  test_interp(0,100,0,0);
  test_interp(0,100,255,99);
  test_interp(-100,100,32,-75);
  test_interp(-100,0,0,-100);
  test_interp(0,-100,128,-50);
  int hz = 44100;

  Wav w = Wav(hz);

  // Write the audio samples
  double seconds = 10;
  int N = hz * seconds;  // total number of samples
  int8_t mem[2];
  uint8_t c1, c2;
  int8_t out;
  for (int i = 0; i < N; ++i)
  {
    c1 = i / 1000;
    c2 = c1+5;
    int8_t x = i&256?127:-127;
    out = bandpass(mem, x, c1, c2);
    //out = interpolate(out, x, c1); // Low-pass filter
    //out = interpolate(0, -100, i); // Sawtooth wave
    w.put( out );
  }
}
