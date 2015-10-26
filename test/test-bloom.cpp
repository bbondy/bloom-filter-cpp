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
    s[i] = rand() % 256;
  }
  s[len] = 0;
}

class BasicHashFn : public HashFn {
public:
  BasicHashFn(int base) : HashFn(0) {
    this->base = base;
  }

  virtual int operator()(const char *input, int len) {
    int total = base;
    for (int i = 0; i < len; i++) {
      total += input[i];
    }
    return total;
  }
private:
  int base;
};


// Can handle long strings
TEST(BloomFilter, BasicLongStrings)
{
  const int bufSize = 20000;
  char id1[bufSize];
  char id2[bufSize];
  char id3[bufSize];
  genRandomBuffer(id1, bufSize);
  genRandomBuffer(id2, bufSize);
  genRandomBuffer(id3, bufSize);

  BasicHashFn hashFns[2] = {BasicHashFn(0), BasicHashFn(1023)};
  BloomFilter b(10, 5000, hashFns, sizeof(hashFns)/sizeof(hashFns[0]));

   b.add(id1, bufSize);
   b.add(id2, bufSize);
   CHECK(b.exists(id1, bufSize));
   CHECK(b.exists(id2, bufSize));
   CHECK(!b.exists("hello"));
   CHECK(!b.exists(id3, bufSize));
}

// supports substringExists
TEST(BloomFilter, substringExists)
{
  BloomFilter b;
  b.add("abc");
  b.add("hello");
  b.add("world");
  CHECK(b.substringExists("hello", 5));
  // Only substrings of length 5 should exist in the bloom filter
  CHECK(!b.substringExists("ell", 3));
  CHECK(b.substringExists("wow ok hello!!!!", 5));
  CHECK(!b.substringExists("he!lloworl!d", 5));
}

// Can return false positives for a saturated set
TEST(BloomFilter, falsePositives)
{
   BloomFilter b(2, 2);
   char sz[64];
   for (int i = 0; i < 100; i++) {
     sprintf(sz, "test-%i", i);
     b.add(sz);
   }
   CHECK(b.exists("test"));
}

 // It cannot return false negatives
 TEST(BloomFilter, noFalseNegatives)
 {
   BloomFilter b;
   char sz[64];
   for (int i = 0; i < 100000; i++) {
     sprintf(sz, "test-%i", i);
     b.add(sz);
   }
   for (int i = 0; i < 100000; i++) {
     sprintf(sz, "test-%i", i);
     CHECK(b.exists(sz));
   }
 }

 // Works with some live examples
 TEST(BloomFilter, liveExamples)
 {
   BloomFilter b;
   b.add("googlesy");
   const char *url1 = "http://tpc.googlesyndication.com/safeframe/1-0-2/html/container.html#xpc=sf-gdn-exp-2&p=http%3A//slashdot.org";
   const char *url2 = "https://tpc.googlesyndication.com/pagead/gadgets/suggestion_autolayout_V2/suggestion_autolayout_V2.html#t=15174732506449260991&p=http%3A%2F%2Ftpc.googlesyndication.com";
   CHECK(b.substringExists("googlesy", 8));
   CHECK(b.substringExists(url1, 8));
   CHECK(b.substringExists(url2, 8));
 }

 // Works by transfering a buffer
 TEST(BloomFilter, transferingBuffer)
 {
   BloomFilter b;
   b.add("Brian");
   b.add("Ronald");
   b.add("Bondy");

   BloomFilter b2(b.getBuffer(), b.getByteBufferSize());
   CHECK(b2.exists("Brian"));
   CHECK(!b2.exists("Brian2"));
   CHECK(!b2.exists("Bria"));

   CHECK(b2.exists("Ronald"));
   CHECK(!b2.exists("Ronald2"));
   CHECK(!b2.exists("onald2"));

   CHECK(b2.exists("Bondy"));
   CHECK(!b2.exists("BrianRonaldBondy"));
   CHECK(!b2.exists("RonaldBondy"));
 }
