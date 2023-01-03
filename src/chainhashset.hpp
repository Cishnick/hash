#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"
#include <iostream>

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

    ChainHashSet(ChainHashSet<Key, HashFunc> const& obj) = delete;
    ChainHashSet(ChainHashSet<Key, HashFunc> && obj) = default;

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

    void replace_impl(Key const& item, Key const& new_item) {
        remove_item_impl(item);
        add_item_impl(new_item);
    }

    void clear_impl() {
        for(auto bucket = table; bucket != table + _capacity; ++bucket)
            bucket->clear();
    }

    void rehash_impl(size_t cap) {
        auto new_table = new std::list<std::string>[cap];

        std::swap(new_table, this->table);
        std::swap(_capacity, cap);
        _count = 0;


        for(auto bucket = new_table; bucket != new_table + cap; ++bucket) {
            for(auto& item : *bucket)
                this->add_item_impl(item);
        }

        delete [] new_table;
    }

    void for_each_impl(std::function<Key(Key const&)> const& func) {
        for(auto bucket = table; bucket != table + _capacity; ++bucket) {
            for(auto& item : *bucket)
                item = func(item);
        }
        rehash_impl(_capacity);
    }


    friend void display(ChainHashSet const &hash);

private:

    std::list<std::string> *table;
    size_t _capacity = 10000;
    size_t _count;
};
