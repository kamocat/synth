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
    const short shift = 23;
    const uint32_t limit = 0x80000000;
    uint32_t a, d, r;
    uint8_t s;
    int32_t time;
    enum {
      idle=0, at=1, dec=2, sus=3, rel=4
    }state;
  public:
    // Attack, Decay, and Release are times in sample ticks
    Envelope(uint32_t attack, uint32_t decay, uint8_t sustain, uint32_t release);
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
    Logvelope(uint32_t attack, uint32_t decay, uint8_t sustain, uint32_t release):Envelope(attack, decay, log2(sustain), release){}
};
