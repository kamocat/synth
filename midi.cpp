#include "midi.hpp"

Note::Note(Logvelope a, Envelope f, uint8_t r, uint8_t l, uint8_t s){
  ps = 1000000 / s; // Sample period (microseconds)
  rate = r;
  level = l;
  fm = f;
  amp = a;
  time = 0;
}

Note::play(uint8_t pitch, uint16_t duration){
  time = duration * 1000; // Duration is ms, time is us
  fm.attack();
  amp.attack();
  amp.update(1);
}

uint8_t Note::getSound(void){
  // Update the time
  int32_t prev = time;
  time -= ps;
  uint8_t ms = (prev>>10) - (time>>10);
  // Update the envelopes
  if(time < 0 ){
    fm.release();
    amp.release();
  }
  uint16_t har = fm.update(ms); // relative harmonic content
  har *= level;
  har >>= 8;
  uint16_t a = amp.update(ms);  // relative amplitude
  
  // Get the next sample
  a *= fm(rate, har, pitch);
  a >>= 8;
  return a;
}

bool Note::busy(void){
  // Should return 0 if not busy
  return amp.update(0);
}
