#pragma once

#include <math.h>
#include "hashFn.h"

/**
 * Implements a Bloom Filter using Rabin Karp for char* buffer lookups
 */
class BloomFilter {
public:
    BloomFilter(unsigned int bitsPerElement = 10, unsigned int estimatedNumElements = 50000, HashFn hashFns[] = nullptr);
    // Used for debuggging
    void print();
    void setBit(unsigned int bitLocation);
    bool isBitSet(unsigned int bitLocation);
private:
  HashFn *hashFns;
  unsigned int byteBufferSize;
  char *buffer;
};
