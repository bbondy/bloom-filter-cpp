/* Copyright (c) 2015 Brian R. Bondy. Distributed under the MPL2 license.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HASHFN_H_
#define HASHFN_H_

// Functor for a hashing function
// Implements a Rabin fingerprint hash function
class HashFn {
 public:
  // Initialize a HashFn with the prime p which is used as the base of the Rabin
  // fingerprint algorithm
  explicit HashFn(int p) {
    this->p = p;
  }

  virtual uint64_t operator()(const char *input, int len,
      unsigned char lastCharCode, uint64_t lastHash) {
    // See the abracadabra example:
    // https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
    return (lastHash - lastCharCode * static_cast<uint64_t>(
          pow(static_cast<long double>(p), len - 1))) * p + input[len - 1];
  }

  virtual uint64_t operator()(const char *input, int len) {
    uint64_t total = 0;
    for (int i = 0; i < len; i++) {
      total += input[i] * static_cast<uint64_t>(
          pow(static_cast<long double>(p), len - i - 1));
    }
    return total;
  }

 private:
  int p;
};

#endif  // HASHFN_H_
