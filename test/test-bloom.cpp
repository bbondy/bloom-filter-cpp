#include "CppUnitLite/TestHarness.h"
#include "CppUnitLite/test.h"
#include "BloomFilter.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include "util.h"
#include "string.h"
#include <iostream>
#include <set>

using namespace std;

TEST(BloomFilter, isBitSetSetBit)
{
  BloomFilter b(10, 3);

  // First bit in a byte
  CHECK(!b.isBitSet(0))
  b.setBit(0);
  CHECK(b.isBitSet(0))

  // Last bit in a byte
  CHECK(!b.isBitSet(7))
  b.setBit(7);
  CHECK(b.isBitSet(7))
  for (int i = 1; i <= 6; i++) {
    CHECK(!b.isBitSet(i));
  }
  CHECK(b.isBitSet(0));

  // Second bit in non first byte
  CHECK(!b.isBitSet(9))
  b.setBit(9);
  CHECK(b.isBitSet(9))
  CHECK(!b.isBitSet(1));
}

// Generates a simple hash function for the specified prime
TEST(BloomFilter, SimpleHashFn)
{
  HashFn H(2);
  int hash = H("hi", 2);

  CHECK(hash == ((int)'h') * pow(2, 1) + ((int)'i') * pow(2, 0));
}

// Detects when elements are in the set and not in the set
TEST(BloomFilter, Basic)
{
   BloomFilter b;
   b.add("Brian");
   b.add("Ronald");
   b.add("Bondy");
   CHECK(b.exists("Brian"));
   CHECK(!b.exists("Brian2"));
   CHECK(!b.exists("Bria"));

   CHECK(b.exists("Ronald"));
   CHECK(!b.exists("Ronald2"));
   CHECK(!b.exists("onald2"));

   CHECK(b.exists("Bondy"));
   CHECK(!b.exists("BrianRonaldBondy"));
   CHECK(!b.exists("RonaldBondy"));
}

void genRandomBuffer(char *s, const int len) {
  for (int i = 0; i < len; ++i) {
    s[i] = alphanum[rand() % 256];
  }
  s[len] = 0;
}
