#include <iostream>
#include "BloomFilter.h"
#include <string.h>

HashFn defaultHashFns[3] = {HashFn(11), HashFn(17), HashFn(23)};

using namespace std;

BloomFilter::BloomFilter(unsigned int bitsPerElement, unsigned int estimatedNumElements, HashFn *hashFns, int numHashFns) :
  hashFns(nullptr), numHashFns(0), byteBufferSize(0), buffer(nullptr) {
  this->hashFns = hashFns;
  this->numHashFns = numHashFns;
  bitBufferSize = bitsPerElement * estimatedNumElements;
  byteBufferSize = bitsPerElement * estimatedNumElements / 8 + 1;
  buffer = new char[byteBufferSize];
  memset(buffer, 0, byteBufferSize);
}

BloomFilter::~BloomFilter() {
  if (buffer) {
    delete[] buffer;
  }
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

void BloomFilter::add(const char *input, int len) {
  for (int j = 0; j < numHashFns; j++) {
    setBit(hashFns[j](input, len) % bitBufferSize);
  }
}

void BloomFilter::add(const char *sz) {
  add(sz, strlen(sz));
}

bool BloomFilter::exists(const char *input, int len) {
  bool allSet = true;
  for (int j = 0; j < numHashFns; j++) {
    allSet = allSet && isBitSet(hashFns[j](input, len) % bitBufferSize);
  }
  return allSet;
}

bool BloomFilter::exists(const char *sz) {
  return exists(sz, strlen(sz));
}
