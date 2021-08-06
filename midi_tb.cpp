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
  Tone bell = Tone(Logvelope(hz/100,hz*2,0,hz), 0x300, &sine);
  Tone fm1 = Tone(Envelope(1, hz, 190, 0), 0x1000, &sine);
  bell.setModulator(fm1, 90);
  Tone bell2 = Tone(bell);

  // Write the audio samples
  int16_t x;
  bell.attack();
  bell.setPitch(0x100);
  for (int i = 0; i < hz*0.8; ++i)
  {
    x = bell.play();
    w.put( x/2 );
  }
  bell2.setPitch(0xE0);
  bell2.attack();
  for (int i = 0; i < hz*2; ++i)
  {
    x = bell.play() + bell2.play();
    w.put( x/2 );
  }
  bell.release();
  bell2.release();
  for (int i = 0; i < hz; ++i)
  {
    x = bell.play() + bell2.play();
    w.put( x/2 );
  }
}
