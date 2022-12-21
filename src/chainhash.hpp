#pragma once

#include <list>
#include <algorithm>
#include <vector>
#include <string>

class ChainHash
{
public:
    explicit ChainHash(size_t size);

    ~ChainHash();

    void add_item(std::string const &item);

    void remove_item(std::string const &item);

    inline size_t count() const
    {
        return _count;
    }

    bool containing(std::string const &item) const;

    friend void display(ChainHash const &hash);

private:
    using hash_t = unsigned long;

    hash_t hash_func(std::string const &data) const;

    std::list<std::string> *table;
    const size_t capacity = 10000;
    size_t _count;
};
