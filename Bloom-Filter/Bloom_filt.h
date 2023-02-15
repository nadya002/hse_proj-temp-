#pragma once

#include <functional>
#include <cmath>
#include <MurmurHash3.h>


template <typename T,
    typename Hash = std::hash<T>>
class BloomFilter 
{
public:
    BloomFilter(size_t max_item, double  = 0.001);

    //void init(size_t max_item, double p = 0.01);

    void insert(T elem);

    bool lookup(T elem) const;

    double bitsPerItem() const;

    ~BloomFilter() {delete array;};

private:
    std::array<uint64_t, 2> _hash(size_t elem) const;
    uint64_t nthHash(size_t n,
                        uint64_t hashA,
                        uint64_t hashB) const;

    const double size_param = log(2.0);
    const size_t min_size = 10;
    size_t size_of_filter, number_of_hash, number_of_elem;
    bool * array = nullptr;

};

template <typename T, typename Hash>
BloomFilter<T, Hash>::BloomFilter(size_t max_item, double p) : number_of_elem(max_item) {
    double lg = -log(p);
    size_of_filter = std::max(min_size, (size_t)((double)max_item * lg / (size_param * size_param)));
    array = new bool[size_of_filter];
    number_of_hash = std::max((size_t)1, (size_t)(lg / size_param));
}

template <typename T, typename Hash>
double BloomFilter<T, Hash>::bitsPerItem() const {
    return (double)(8.0 * size_of_filter * sizeof(T)) / (double)number_of_elem;
}

template <typename T, typename Hash>
std::array<uint64_t, 2> BloomFilter<T, Hash>::_hash(size_t elem) const {
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128((&elem), sizeof(size_t), 0, hashValue.data());

     return hashValue;
}

template <typename T, typename Hash>
uint64_t BloomFilter<T, Hash>::nthHash(size_t n,
                        uint64_t hashA,
                        uint64_t hashB)  const {
    return (hashA + n * hashB) % size_of_filter;
}

template <typename T, typename Hash>
void BloomFilter<T, Hash>::insert(T elem) {
    size_t _ha = Hash{}(elem);
    std::array<uint64_t, 2> hashValues = _hash(_ha);
    for (size_t n = 0; n < number_of_hash; n++) {
      array[nthHash(n, hashValues[0], hashValues[1])] = true;
    }
}

template <typename T, typename Hash>
bool BloomFilter<T, Hash>::lookup(T elem) const {
    size_t _ha = Hash{}(elem);
    std::array<uint64_t, 2> hashValues = _hash(_ha);

    for (int n = 0; n < number_of_hash; n++) {
        if (!array[nthHash(n, hashValues[0], hashValues[1])]) {
            return false;
        }
    }

    return true;
}