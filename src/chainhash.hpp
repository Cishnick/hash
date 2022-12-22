#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"


template<class T, template<class U,class V> class HashFunc>
class ChainHash
{
    using hash_t = size_t;
    using _HashFunc = HashFunc<T, hash_t>;

public:
    explicit ChainHash(size_t size) :
        capacity(size),
        _count(0)
    {
        table = new std::list<std::string>[capacity];
    }

    ~ChainHash() {
        delete[] table;
    }

    void add_item(std::string const &item){
        _count++;
        auto key = hash_func(item);
        table[key].push_back(item);
    }

    void remove_item(std::string const &item){
        _count--;
        auto key = hash_func(item);
        table[key].remove(item);
    }

    inline size_t count() const
    {
        return _count;
    }

    bool containing(std::string const &item) const {
        auto key = hash_func(item);
        auto chain = table[key];
        return std::find(chain.cbegin(), chain.cend(), item) != chain.cend();
    }

    friend void display(ChainHash const &hash);

private:
    hash_t hash_func(T const &data) const {
        return _HashFunc::get(data, capacity);
    }

    std::list<std::string> *table;
    const unsigned capacity = 10000;
    unsigned _count;
};
