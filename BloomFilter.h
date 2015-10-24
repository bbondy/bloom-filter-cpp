typedef void (*HashFn)(char *buffer, int len, int lastHash);

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
