#include "BloomFilter.h"
#include <iostream>
using namespace std;

char separatorBuffer[32] = { 0, 0, 0, 0, 0, -128, 0, -92, 0, 0, 0, 64 };
inline bool isSeparatorChar(char c) {
  return !!(separatorBuffer[c / 8] & 1 << c % 8);
}

int main(int argc, char**argv) {
  BloomFilter bloomFilter(8, 32);
  bloomFilter.setBit((int)':');
  bloomFilter.setBit((int)'?');
  bloomFilter.setBit((int)'/');
  bloomFilter.setBit((int)'=');
  bloomFilter.setBit((int)'^');
  cout << "size: " << bloomFilter.getByteBufferSize() << endl;
  for (int i = 0; i < bloomFilter.getByteBufferSize(); i++) {
    cout << " " << (int)bloomFilter.getBuffer()[i];
  }
  cout << endl;

  cout << "Separator chars: " << isSeparatorChar(':') << " " <<  isSeparatorChar('?') << " " <<  isSeparatorChar('/') << " "
    <<  isSeparatorChar('=') <<  isSeparatorChar('^')  << endl;

  cout << "NON Separator chars: " << isSeparatorChar('a') << " " <<  isSeparatorChar('!') << " " <<  isSeparatorChar('#') << " "
    <<  isSeparatorChar('X') <<  isSeparatorChar('.') <<  isSeparatorChar('\\') << isSeparatorChar('"') << isSeparatorChar(-128) << endl;



  return 0;
}
