#include <stdint.h>

#pragma once

class SineTable{
    uint8_t len;
    int8_t * data;
  public:
    SineTable();
    ~SineTable(void);
    int8_t lookup(int8_t index);
};


class Envelope{
    const uint16_t limit = 0x8000;
    uint16_t a, d, r;
    uint8_t s;
    int16_t time;
    enum {
      idle=0, at, dec, sus, rel
    }state;
  public:
    // Attack, Decay, and Release are times in sample ticks
    Envelope(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release);
    Envelope(const Envelope & src);
    uint8_t update(void);
    void attack(void);
    void release(void);
    uint8_t getState(void);
};

class Logvelope: public Envelope{
  public:
    static uint8_t log2(uint8_t x);
    static uint8_t exp2(uint8_t x);
    uint8_t update(void);
    Logvelope(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release):Envelope(attack, decay, log2(sustain), release){}
};
