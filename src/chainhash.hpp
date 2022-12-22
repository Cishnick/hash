#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"

#include "HashSet.hpp"

template<class Key, template<class U,class V> class HashFunc>
class ChainHash : public HashSet<Key, HashFunc>
{
public:
    explicit ChainHash(size_t size) :
        _capacity(size),
        _count(0)
    {
        table = new std::list<Key>[_capacity];
    }

    ~ChainHash() {
        delete[] table;
    }

    virtual void add_item(Key const &item) override{
        _count++;
        auto key = HashSet<Key, HashFunc>::hash_func(item);
        table[key].push_back(item);
    }

    virtual void add_item(Key && item) override{
        _count++;
        auto key = HashSet<Key, HashFunc>::hash_func(item);
        table[key].push_back(std::forward<Key>(item));
    }

    virtual void remove_item(Key const &item) override {
        _count--;
        auto key = HashSet<Key, HashFunc>::hash_func(item);
        table[key].remove(item);
    }

    virtual size_t count() const override
    {
        return _count;
    }

    virtual size_t capacity() const override
    {
        return _capacity;
    }

    virtual bool empty() const override
    {
        return _count == 0;
    }

    virtual bool containing(Key const &item) const override {
        auto key = HashSet<Key, HashFunc>::hash_func(item);
        auto chain = table[key];
        return std::find(chain.cbegin(), chain.cend(), item) != chain.cend();
    }

    virtual Key& find(Key const& item) override {
        auto key = HashSet<Key, HashFunc>::hash_func(item);
        auto chain = table[key];
        // Exception!
        return *std::find(chain.begin(), chain.end(), item);
    }

    virtual void clear() override {
        for(auto bucket = table; bucket != table + _capacity; ++bucket)
            bucket->clear();
    }

    virtual void rehash(size_t) {
        
    }

    virtual void for_each(std::function<Key(Key const&)> const& func) override {
        for(auto bucket = table; bucket != table + _capacity; ++bucket) {
            for(auto& item : *bucket)
                item = func(item);
        }
    }


    friend void display(ChainHash const &hash);

private:
    std::list<std::string> *table;
    const unsigned _capacity = 10000;
    unsigned _count;
};
