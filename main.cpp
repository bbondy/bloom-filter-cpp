#include "BloomFilter.h"

int main(int argc, char**argv) {
  BloomFilter bloomFilter(10, 4);

  bloomFilter.print();
  return 0;
}
