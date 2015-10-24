#pragma once

#include <math.h>
#include "hashFn.h"

extern HashFn defaultHashFns[3];
/**
 * Implements a Bloom Filter using Rabin Karp for char* buffer lookups
 */
class BloomFilter {
public:
    BloomFilter(unsigned int bitsPerElement = 10, unsigned int estimatedNumElements = 50000, HashFn hashFns[] = defaultHashFns, int numHashFns = sizeof(defaultHashFns)/sizeof(defaultHashFns[0]));
    ~BloomFilter();
    // Used for debuggging
    void print();
    void setBit(unsigned int bitLocation);
    bool isBitSet(unsigned int bitLocation);
    // Adds the specified buffer to the bloom filter
    void add(const char *input, int len);
    void add(const char *sz);

    /**
     * Checks whether an element probably exists in the set, or definitely doesn't.
     * @param str Either a string to check for existance or an array of the string's char codes
     *   The main reason why you'd want to pass in a char code array is because passing a string
     *   will use JS directly to get the char codes which is very inneficient compared to calling
     *   into C++ code to get it and then making the call.
     *
     * Returns true if the element probably exists in the set
     * Returns false if the element definitely does not exist in the set
     */
    bool exists(const char *input, int len);
    bool exists(const char *sz);

private:
  HashFn *hashFns;
  int numHashFns;
  unsigned int byteBufferSize;
  unsigned int bitBufferSize;
  char *buffer;
};
