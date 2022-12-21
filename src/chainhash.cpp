#include "chainhash.hpp"


ChainHash::ChainHash(size_t size) :
    capacity(size),
    _count(0)
{
    table = new std::list<std::string>[capacity];
}

ChainHash::~ChainHash() {
    delete[] table;
}

void ChainHash::add_item(std::string const& item) {
        _count++;
        auto key = hash_func(item);
        table[key].push_back(item);
}

void ChainHash::remove_item(std::string const& item) {
    _count--;
    auto key = hash_func(item);
    table[key].remove(item);
}

bool ChainHash::containing(std::string const& item) const {
    auto key = hash_func(item);
    auto chain = table[key];
    return std::find(chain.cbegin(), chain.cend(), item) != chain.cend();
}

ChainHash::hash_t ChainHash::hash_func(std::string const& data) const {
    hash_t i = 0;
    for(auto sym : data)
        i += sym;
    return i % capacity;
}
