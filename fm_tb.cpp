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
  int8_t mem[2];
  uint8_t c1;
  int16_t x;
  init_fm();
  Logvelope amp = Logvelope(10,3*hz,0,0);
  amp.attack();
  for (int i = 0; i < hz*0.8; ++i)
  {
    c1 = i / 1000;
    uint8_t dt = i%44?0:1;
    x = amp.update();
    x *= fm(16, 255-c1, 4);
    x >>= 8;
    w.put( x );
  }
  amp.attack();
  for (int i = 0; i < hz*5; ++i)
  {
    c1 = i / 1000;
    uint8_t dt = i%44?0:1;
    x = amp.update();
    x *= fm(16, 255-c1, 3);
    x >>= 8;
    w.put( x );
  }
}
