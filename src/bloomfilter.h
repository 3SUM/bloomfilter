#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>

#include "MurmurHash3.h"

namespace kitana {
template <typename T>
class bloomfilter {
   private:
    // Expected number of elements n
    static constexpr uint64_t n = 256;

    // Size of bit array m
    // Calculated by: m = -((nlnp)/(ln2)^2)
    static constexpr uint64_t m = 1596;

    // Number of hash functions k
    // Calculated by: k = (m/n)ln2
    static constexpr uint8_t k = 4;

    // Probability of false positive p
    static constexpr float p = 0.05;

    // Bloom filter
    std::bitset<m> filter;

   public:
    bloomfilter() = default;
    ~bloomfilter() = default;

    std::array<uint64_t, 2> hash(const T *key) {
        std::array<uint64_t, 2> hashes;
        MurmurHash3_x64_128(key, sizeof(key), 0, hashes.data());
        return hashes;
    }

    inline uint64_t nthhash(uint8_t n, uint64_t hashA, uint64_t hashB) {
        return (hashA + n + hashB) % m;
    }

    void add(const T *key) {
        auto hashes = hash(key);

        for (uint8_t n = 0; n < k; n++) {
            filter[nthhash(n, hashes[0], hashes[1])] = true;
        }
    }

    bool query(const T *key) {
        auto hashes = hash(key);

        for (uint8_t n = 0; n < k; n++) {
            if (!filter[nthhash(n, hashes[0], hashes[1])]) {
                return false;
            }
        }

        return true;
    }
};
}  // namespace kitana
