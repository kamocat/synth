#include "midi.hpp"

Tone::Tone(const Envelope &amplitude, uint16_t fundemental, SineTable * w){
  root = fundemental;
  amp = new Envelope(amplitude);
  fm = 0; // NULL
  level = 0;
  wave = w;
  t = 0;
  dt = 1;
}

Tone::Tone(const Tone &src){
  root = src.root;
  amp = new Envelope(*(src.amp));
  if(src.fm)
    fm = new Tone(*(src.fm));
  else
    fm = 0;
  level = src.level;
  wave = src.wave;
  t = src.t;
  dt = src.dt;
}

Tone::~Tone(void){
  delete fm;
  delete amp;
}

void Tone::setEnvelope(Envelope amplitude){
  delete amp;
  amp = new Envelope(amplitude);
}

Envelope Tone::getEnvelope(void){
  return *amp;
}

void Tone::setModulator(Tone m, uint8_t l){
  fm = new Tone(m);
  level = l;
}

Tone Tone::getModulator(void){
  return *fm;
};

void Tone::setPitch(uint16_t pitch){
  // 8.8 fixed-point multiply
  uint32_t tmp = pitch;
  tmp *= root;
  tmp >>= 8;
  dt = tmp;
}

int8_t Tone::play(void){
  if(level){
    int16_t mod = level;
    mod *= fm->play();
    t += mod;
  }
  t += dt;
  int16_t out = wave->lookup(t>>8);
  out *= amp->update();
  out >>= 8;
  return out;
}

void Tone::attack(void){
  if(fm)
    fm->attack();
  amp->attack();
}

void Tone::release(void){
  if(fm)
    fm->release();
  amp->release();
}

bool Tone::busy(void){
  return (0 != amp->getState());
}
