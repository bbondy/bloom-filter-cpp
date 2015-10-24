#include <iostream>
#include "BloomFilter.h"
#include <string.h>

using namespace std;

BloomFilter::BloomFilter(unsigned int bitsPerElement, unsigned int estimatedNumElements, HashFn hashFns[]) :
  hashFns(nullptr), byteBufferSize(0), buffer(nullptr) {
  this->hashFns = hashFns;
  byteBufferSize = bitsPerElement * estimatedNumElements / 8 + 1;
  buffer = new char[byteBufferSize];
  memset(buffer, 0, byteBufferSize);
}

void BloomFilter::print() {
  for (unsigned int i = 0; i < byteBufferSize; i++) {
    int mask = 0x01;
    for (int j = 0; j < 8; j++) {
        cout << ((buffer[i] & mask) ? "1" : "0");
        mask <<= 1;
    }
    cout << " ";
  }
}

void BloomFilter::setBit(unsigned int bitLocation) {
  buffer[bitLocation / 8] |= 1 << bitLocation % 8;
}

bool BloomFilter::isBitSet(unsigned int bitLocation) {
  return !!(buffer[bitLocation / 8] & 1 << bitLocation % 8);
}
