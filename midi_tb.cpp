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
  Tone bell = Tone(Logvelope(hz/100,10*hz,0,hz/2), 0x100, &sine);
  Tone fm1 = Tone(Envelope(10, hz, 120, hz), 0x307, &sine);
  bell.setModulator(fm1, 15);
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
