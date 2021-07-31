#include "audio.hpp"

Audio::Audio(){
}
void Audio::put(int8_t sample){
}
Audio::~Audio(){
}

Wav::Wav(uint16_t fs) : Audio(){
  f = std::ofstream("sample.wav", std::ios::binary);

  f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  write(16, 4 );  // no extension data
  write( 1, 2 );  // PCM - integer samples
  write( 1, 2 );  // one channel (mono file)
  write(fs, 4 );  // samples per second (Hz)
  write(fs, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
  write( 1, 2 );  // data block size
  write( 8, 2 );  // number of bits per sample (use a multiple of 8)

  // Write the data chunk header
  data_chunk_pos = f.tellp();
  f << "data----";  // (chunk size to be filled in later)
}

void Wav::put(int8_t x){
  f.put(x + 128); // 8-bit PCM is unsigned
}

void Wav::write(uint32_t data, int size){
  for(; size; --size, data>>=8){
    f.put( static_cast <char> (data & 0xFF) );
  }
}

Wav::~Wav(){
  // (We'll need the final file size fot fix the chunk sizes above)
  size_t file_length = f.tellp();

  // fix the data chunk header to contain the data size
  f.seekp( data_chunk_pos + 4 );
  write(file_length - data_chunk_pos + 8, 4);

  //Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  f.seekp( 0 + 4 );
  write(file_length - 8, 4 ); 
}
