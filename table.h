#include <stdint.h>
class SineTable{
    uint8_t len;
    int8_t * data;
  public:
    SineTable();
    ~SineTable(void);
    int8_t lookup(int8_t index)
}
