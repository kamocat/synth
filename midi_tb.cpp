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
  Tone bell = Tone(Logvelope(hz/100,3*hz,0,hz/4), 0x100, &sine);
  bell.setModulator(Tone(Envelope(hz/100, hz, 120, hz/4), 0x2EE, &sine), 80);

  // Write the audio samples
  double seconds = 5;
  int N = hz * seconds;  // total number of samples
  int8_t x;
  bell.attack();
  for (int i = 0; i < N; ++i)
  {
    x = bell.play();
    w.put( x );
  }
}
