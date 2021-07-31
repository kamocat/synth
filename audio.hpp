#include <stdint.h>
#include <fstream>

class Audio{
  public:
    Audio();
    virtual void put(int8_t sample);
    virtual ~Audio();
};
    
class Wav : public Audio {
    std::ofstream f;
    size_t data_chunk_pos;
    void write(uint32_t data, int size);
  public:
    Wav(uint16_t fs);
    void put(int8_t sample);
    ~Wav();
};
  
