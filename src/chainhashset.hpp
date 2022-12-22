#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"

#include "HashSet.hpp"

template<class Key, template<class U,class V> class HashFunc>
class ChainHashSet : public HashSet<ChainHashSet<Key, HashFunc>, Key, HashFunc>
{
public:
    explicit ChainHashSet(size_t size) :
        _capacity(size),
        _count(0)
    {
        table = new std::list<Key>[_capacity];
    }

    ~ChainHashSet() {
        delete[] table;
    }

    void add_item_impl(Key const &item) {
        _count++;
        auto key = HashSet<ChainHashSet, Key, HashFunc>::hash_func(item);
        table[key].push_back(item);
    }

    void add_item_impl(Key && item) {
        _count++;
        auto key = HashSet<ChainHashSet, Key, HashFunc>::hash_func(item);
        table[key].push_back(std::forward<Key>(item));
    }

    void remove_item_impl(Key const &item)  {
        _count--;
        auto key = HashSet<ChainHashSet, Key, HashFunc>::hash_func(item);
        table[key].remove(item);
    }

    size_t count_impl() const 
    {
        return _count;
    }

    size_t capacity_impl() const 
    {
        return _capacity;
    }

    bool empty_impl() const 
    {
        return _count == 0;
    }

    bool containing_impl(Key const &item) const {
        auto key = HashSet<ChainHashSet, Key, HashFunc>::hash_func(item);
        auto chain = table[key];
        return std::find(chain.cbegin(), chain.cend(), item) != chain.cend();
    }

    Key& find_impl(Key const& item) {
        auto key = HashSet<ChainHashSet, Key, HashFunc>::hash_func(item);
        auto chain = table[key];
        // Exception!
        return *std::find(chain.begin(), chain.end(), item);
    }

    void clear_impl() {
        for(auto bucket = table; bucket != table + _capacity; ++bucket)
            bucket->clear();
    }

    void rehash_impl(size_t) {
        
    }

    void for_each_impl(std::function<Key(Key const&)> const& func) {
        for(auto bucket = table; bucket != table + _capacity; ++bucket) {
            for(auto& item : *bucket)
                item = func(item);
        }
    }


    friend void display(ChainHashSet const &hash);

private:
    std::list<std::string> *table;
    const unsigned _capacity = 10000;
    unsigned _count;
};
