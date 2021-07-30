#include <stdint.h>

#ifndef SINE_HEADER
#define SINE_HEADER

class SineTable{
    uint8_t len;
    int8_t * data;
  public:
    SineTable();
    ~SineTable(void);
    int8_t lookup(int8_t index);
};

#endif
