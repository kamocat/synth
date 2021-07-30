#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "table.hpp"
using namespace std;

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
  ofstream f( "table.wav", ios::binary );

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
  double seconds = 2.5;
  int N = hz * seconds;  // total number of samples
  int16_t out;
  SineTable cos = SineTable();
  Envelope e = Envelope(100,50,200,20);
  for (int i = 0; i < N ; ++i)
  {
    uint8_t dt = 0==i%44?1:0;
    out = e.update(dt, i<hz*2);
    out *= cos.lookup(i);
    out >>= 8;
    write_word( f, out+128, 1 );
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
