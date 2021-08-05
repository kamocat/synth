#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "midi.hpp"
#include "audio.hpp"



int main()
{
  int hz = 44100;

  Wav w = Wav(hz);

  // Configure the synth
  SineTable sine;
  Tone bell = Tone(Logvelope(hz/100,3*hz,0,hz/20), 0x100, &sine);
  Tone fm1 = Tone(Envelope(1, hz, 0, hz/4), 0x2EE, &sine);
  bell.setModulator(fm1, 10);
  bell.setPitch(0x234);

  // Write the audio samples
  double seconds = 2;
  int N = hz * seconds;  // total number of samples
  int8_t x;
  bell.attack();
  for (int i = 0; i < N; ++i)
  {
    x = bell.play();
    w.put( x );
  }
  bell.release();
  for (int i = 0; i < N/2; ++i)
  {
    x = bell.play();
    w.put( x );
  }
}
