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
private:
    ChainHashSet() :
        _capacity(0),
        _count(0),
        table(nullptr)
    {}
    

public:
    
    void swap(ChainHashSet& other) noexcept {
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_count, other._count);
        std::swap(this->table, other.table);
    }
    
    explicit ChainHashSet(size_t size) :
        _capacity(size),
        _count(0),
        table(new std::list<Key>[size])
    {
    }

    ChainHashSet clone() {
        return *this;
    }

    ChainHashSet(ChainHashSet<Key, HashFunc> const& obj) : 
        _capacity(obj._capacity),
        _count(obj._count),
        table(new std::list<Key>[obj._capacity])
    {
        std::cout << "copy";
        auto ptable = table;
        for(auto bucket = obj.table; bucket != obj.table + obj._capacity; ++bucket, ++ptable) {
            *ptable = *bucket;
        }
    }

    ChainHashSet(ChainHashSet<Key, HashFunc> && obj) :
        ChainHashSet()
    {
        std::cout << "move";
        this->swap(obj);
    }

    ChainHashSet<Key, HashFunc>& operator=(ChainHashSet<Key, HashFunc> other) {
        std::cout << "copy";
        if(this == &other)
            return *this;

        this->swap(other);

        return *this;
    }

    ChainHashSet<Key, HashFunc>& operator=(ChainHashSet<Key, HashFunc>&& other) {
        std::cout << "move";
        if(this == &other)
            return *this;

        ChainHashSet<Key, HashFunc> swap_obj;
        this->swap(swap_obj);

        this->swap(other);

        return *this;        
    }

    ~ChainHashSet() {
        if(table)
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
        auto swap_table = new std::list<std::string>[cap];

        std::swap(swap_table, this->table);
        std::swap(_capacity, cap);
        _count = 0;

        for(auto bucket = swap_table; bucket != swap_table + cap; ++bucket) {
            for(auto& item : *bucket)
                this->add_item_impl(item);
        }

        delete [] swap_table;
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
