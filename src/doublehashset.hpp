#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"

#include "HashSet.hpp"

template<class Key, template<class U,class V> class HashFunc>
class DoubleHashSet : public HashSet<DoubleHashSet<Key, HashFunc>, Key>
{
private:
    DoubleHashSet() :
        _capacity(0),
        _count(0)
    {}
    
public:    
    void swap(DoubleHashSet& other) noexcept {
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_count, other._count);
        // Todo add
    }
    
    explicit DoubleHashSet(size_t size) :
        _capacity(size),
        _count(0)
    {
    }

    DoubleHashSet clone() {
        return *this;
    }

    DoubleHashSet(DoubleHashSet<Key, HashFunc> const& obj) : 
        _capacity(obj._capacity),
        _count(obj._count)
    {
    }

    DoubleHashSet(DoubleHashSet<Key, HashFunc> && obj) :
        DoubleHashSet()
    {
        this->swap(obj);
    }

    DoubleHashSet<Key, HashFunc>& operator=(DoubleHashSet<Key, HashFunc> other) {
        if(this == &other)
            return *this;

        this->swap(other);

        return *this;
    }

    DoubleHashSet<Key, HashFunc>& operator=(DoubleHashSet<Key, HashFunc>&& other) {
        if(this == &other)
            return *this;

        DoubleHashSet<Key, HashFunc> swap_obj;
        this->swap(swap_obj);

        this->swap(other);

        return *this;        
    }

    ~DoubleHashSet() {
    }

    void add_item_impl(Key const &item) {
    }

    void add_item_impl(Key && item) {
    }

    void remove_item_impl(Key const &item)  {
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
    }

    void replace_impl(Key const& item, Key const& new_item) {
    }

    void clear_impl() {
    }

    void rehash_impl(size_t cap) {
    }

    void for_each_impl(std::function<Key(Key const&)> const& func) {
    }

    friend void display(DoubleHashSet const &hash);

private:
    size_t _capacity;
    size_t _count;
    Key* table;
};
