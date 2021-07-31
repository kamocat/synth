#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "table.hpp"
#include "audio.hpp"

void test_log2(void){
  // Is it monotonic?
  int next, prev;
  prev = 0;
  for(int i = 0; i < 256; ++i){
    next = Logvelope::log2(i);
    if(next<prev){
      std::cout<<"log2 is not monotonic"<<std::endl;
      break;
    }
    prev = next;
  }
}
void test_exp2(void){
  int next, prev;
  // Is it monotonic?
  prev = 0;
  for(int i = 0; i < 256; ++i){
    next = Logvelope::exp2(i);
    if(next<prev){
      std::cout<<"exp2 is not monotonic"<<std::endl;
      break;
    }
    prev = next;
  }
}


int main()
{
  test_log2();
  test_exp2();
  int hz = 44100;

  Wav w = Wav(hz);

  // Write the audio samples
  double seconds = 1;
  int N = hz * seconds;  // total number of samples
  int16_t x;
  SineTable cos = SineTable();
  Envelope e = Envelope(100,50,200,200);
  for (int i = 0; i < N ; ++i)
  {
    uint8_t dt = 0==i%44?1:0;
    x = e.update(dt, i<hz*.5);
    x *= cos.lookup(i);
    x >>= 8;
    w.put( x );
  }
}
