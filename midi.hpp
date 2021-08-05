#include <stdint.h>
#include "table.hpp"
#include "fm.h"

class Note{
  public:
    Note(Logvelope amplitude, Envelope fm, uint8_t rate, uint8_t level, uint16_t sample_frequency);
    void play(uint8_t pitch, uint16_t duration);
    int8_t getSound(void);
    bool busy(void);
  private:
    int32_t time;
    uint16_t ps;
    Envelope fm;
    Logvelope amp;
    uint8_t rate;
    uint8_t level;
};

