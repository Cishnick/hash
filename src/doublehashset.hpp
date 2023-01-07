#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "hashfunctions.hpp"

#include "HashSet.hpp"
#include <cmath>

template<class Key, template<class DataType, class KeyType> class HashFunc1, template<class DataType, class KeyType> class HashFunc2>
class DoubleHashSet : public HashSet<DoubleHashSet<Key, HashFunc1, HashFunc2>, Key>
{
private:
    DoubleHashSet() :
        _capacity(0),
        _count(0),
        table(nullptr)
    {}
    
    using hash_t = size_t;

    auto hash1(Key const& data) const {
        return HashFunc1<Key, hash_t>::get(data, _capacity);
    }

    // value must be a no zero and uneven number
    auto hash2(Key const& data) const {
        auto hash = 2 + HashFunc2<Key, hash_t>::get(data, _capacity - 2); 
        return hash - 1 + hash % 2;
    }

public:    
    void swap(DoubleHashSet& other) noexcept {
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_count, other._count);
        std::swap(this->table, other.table);
    }
    
    explicit DoubleHashSet(size_t pow_size) :
        _capacity(1 << pow_size),
        _count(0),
        table(new Cell[_capacity])
    {
    }

    DoubleHashSet(DoubleHashSet const& obj) : 
        _capacity(obj._capacity),
        _count(obj._count),
        table(new Cell[_capacity])
    {
        std::copy(obj.table, obj.table + obj._capacity, this->table);
    }

    DoubleHashSet(DoubleHashSet && obj) :
        DoubleHashSet()
    {
        this->swap(obj);
    }

    DoubleHashSet& operator=(DoubleHashSet other) {
        if(this == &other)
            return *this;

        this->swap(other);

        return *this;
    }

    DoubleHashSet& operator=(DoubleHashSet&& other) {
        if(this == &other)
            return *this;

        DoubleHashSet swap_obj;
        this->swap(swap_obj);
        this->swap(other);

        return *this;        
    }

    ~DoubleHashSet() {
        delete [] table;
    }

    void add_item_impl(Key const &item) {
        auto ind = hash1(item);
        auto step = hash2(item);
        while(table[ind].busy)
            ind = (ind + step) % _capacity;
        
        table[ind].data = item;
        table[ind].deleted = false;
        table[ind].busy = true;
        _count++;
    }

    void add_item_impl(Key && item) {
        auto ind = hash1(item);
        auto step = hash2(item);
        while(table[ind].busy)
            ind = (ind + step) % _capacity;
        
        std::swap(table[ind].data, item);

        table[ind].deleted = false;
        table[ind].busy = true;
        _count++;
    }

    void remove_item_impl(Key const &item) {
        auto ind = hash1(item);
        auto step = hash2(item);
        while(table[ind].busy) {
            if(table[ind].data == item)
                table[ind].deleted = true;
            ind = (ind + step) % _capacity;
        }
        _count--;
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
        auto ind = hash1(item);
        auto step = hash2(item);
        while(table[ind].busy) {
            if((!table[ind].deleted) && table[ind].data == item)
                return true;
            ind = (ind + step) % _capacity;
        }
        return false;
    }

    void replace_impl(Key const& item, Key const& new_item) {
        remove_item_impl(item);
        add_item_impl(new_item);
    }

    void clear_impl() {
        std::for_each(table, table + _capacity, [](Cell const& cell) {
            cell.data = Key();
            cell.busy = false;
            cell.deleted = true;
        });
        _count = 0;

    }

    void rehash_impl(size_t cap) {
        auto size = static_cast<size_t>(1 << cap);
        auto new_table = new Cell[size];
        
        std::swap(this->table, new_table);
        std::swap(this->_capacity, size);
        this->_count = 0;

        std::for_each(new_table, new_table + size, [this](Cell const& cell) {
            if(cell.busy && !cell.deleted)
                this->add_item_impl(cell.data);
        });

        delete[]  new_table;
    }

    void for_each_impl(std::function<Key(Key const&)> const& func) {
        std::for_each(table, table + _capacity, [func](Cell& cell) {
            if(cell.busy && !cell.deleted)
                cell.data = func(cell.data);
        });
        rehash_impl(static_cast<size_t>(std::log2(_capacity)));
    }

    friend void display(DoubleHashSet const &hash);

private:
    size_t _capacity;
    size_t _count;

    struct Cell {
        Key data;
        bool busy = false;
        bool deleted = true;
    }* table;

};
