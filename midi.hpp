#include <stdint.h>
#include "table.hpp"

class Tone{
  public:
    Tone(const Envelope &amplitude, uint16_t fundemental, SineTable * waveform);
    Tone(const Tone &src);
    ~Tone(void);
    void setEnvelope(Envelope amplitude);
    Envelope getEnvelope(void);
    void setModulator(Tone m, uint8_t level);
    Tone getModulator(void);
    void setPitch(uint16_t pitch);
    int8_t play(void);
    void attack(void);
    void release(void);
    bool busy(void);
  private:
    Tone * fm;
    Envelope * amp;
    SineTable * wave;
    uint16_t dt, root, t;
    uint8_t level;
};
