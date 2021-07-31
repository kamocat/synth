#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "fm.h"
#include "table.hpp"
#include "audio.hpp"



int main()
{
  int hz = 44100;

  Wav w = Wav(hz);

  // Write the audio samples
  double seconds = 5;
  int N = hz * seconds;  // total number of samples
  int8_t mem[2];
  uint8_t c1, c2;
  int16_t x;
  init_fm();
  Logvelope amp = Logvelope(10,3000,0,0);
  for (int i = 0; i < N; ++i)
  {
    c1 = i / 1000;
    uint8_t dt = i%44?0:1;
    x = amp.update(dt, 0==i);
    x *= fm(16, 255-c1, 3);
    x >>= 8;
    w.put( x );
  }
}
