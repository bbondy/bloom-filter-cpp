[![Build Status](https://travis-ci.org/bbondy/bloom-filter-cpp.svg?branch=master)](https://travis-ci.org/bbondy/bloom-filter-cpp)

# BloomFilter.cpp
Bloom filter written in C++. Tests whether an element belongs to a set. False positive matches are possible, false negatives are not. Also implements Rabin–Karp algorithm with Rabin fingerprint hashes for multiple substring searches.

This is a port of a [similar lib](https://github.com/bbondy/bloom-filter-js) I prototyped in JS.

## To include bloom-filter-cpp in your project:

```
npm install --save bloom-filter-cpp
```

## Usage

```c++
#include "BloomFilter.h"
#include <iostream>

using namespace std;

int main(int argc, char**argv) {
  BloomFilter b;
  b.add("Brian");
  b.add("Ronald");
  b.add("Bondy");

  // Prints true
  cout << (b.exists("Brian") ? "true" : "false") << endl;

  // Prints false
  cout << (b.exists("Brian Ronald") ? "true" : "false") << endl;

  // Create a new BloomerFilter form a previous serialization
  BloomFilter b2(b.getBuffer(), b.getByteBufferSize());

  // Prints the same as above
  cout << (b2.exists("Brian") ? "true" : "false") << endl;
  cout << (b2.exists("Brian Ronald") ? "true" : "false") << endl;

  // And you can check if any substring of a passed string exists
  // Prints true
  cout << (b.substringExists("Hello my name is Brian", 5) ? "true" : "false") << endl;
  // Prints false
  cout << (b.substringExists("Hello my name is Bri", 3) ? "true" : "false") << endl;

  return 0;
}
```


## Developing bloom-filter-cpp

````
git clone bloom-filter-cpp
npm install
```

## Build everything in release

```
make
```

## Build everything in debug

```
make build-debug
```

## Running sample

```
make sample
```

## Running tests

```
make test
```

## Clearing build files
```
make clean
```
