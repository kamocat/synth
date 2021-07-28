#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "filter.h"
using namespace std;

int test_interp(int a, int b, unsigned int c, int y){
  int tmp = interpolate(a,b,c);
  bool pass = y==tmp;
  std::cout << a<< ".." << b<< "@" << c << "=" << tmp 
    << ":\t"<<(pass?"PASS":"FAIL")<<std::endl;
  return !pass;
}

namespace little_endian_io
{
  template <typename Word>
    std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
    {
      for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
      return outs;
    }
}
using namespace little_endian_io;

int main()
{
  test_interp(0,100,128,50);
  test_interp(0,100,0,0);
  test_interp(0,100,255,99);
  test_interp(-100,100,32,-75);
  test_interp(-100,0,0,-100);
  test_interp(0,-100,128,-50);
  ofstream f( "filter.wav", ios::binary );

  // Write the file headers
  f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  write_word( f,     16, 4 );  // no extension data
  write_word( f,      1, 2 );  // PCM - integer samples
  write_word( f,      1, 2 );  // one channel (mono file)
  write_word( f,  44100, 4 );  // samples per second (Hz)
  write_word( f,  44100, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
  write_word( f,      1, 2 );  // data block size
  write_word( f,      8, 2 );  // number of bits per sample (use a multiple of 8)

  // Write the data chunk header
  size_t data_chunk_pos = f.tellp();
  f << "data----";  // (chunk size to be filled in later)

  // Write the audio samples
  int hz = 44100;
  double seconds = 10;
  int N = hz * seconds;  // total number of samples
  int8_t mem[2];
  uint8_t c1, c2;
  int8_t out;
  for (int i = 0; i < N; ++i)
  {
    c1 = i / 1000;
    c2 = c1+5;
    int8_t x = i&256?127:-127;
    out = bandpass(mem, x, c1, c2);
    //out = interpolate(out, x, c1); // Low-pass filter
    //out = interpolate(0, -100, i); // Sawtooth wave
    write_word( f, out+127, 1 );
  }

  // (We'll need the final file size fot fix the chunk sizes above)
  size_t file_length = f.tellp();

  // fix the data chunk header to contain the data size
  f.seekp( data_chunk_pos + 4 );
  write_word( f, file_length - data_chunk_pos + 8 );

  //Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  f.seekp( 0 + 4 );
  write_word( f, file_length - 8, 4 ); 
}
