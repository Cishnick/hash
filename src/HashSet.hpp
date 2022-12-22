#pragma once
#include <functional>

template<class Key, template<class U,class V> class HashFunc>
class HashSet {
protected:
    using hash_t = size_t;
    
private:

    using _HashFunc = HashFunc<Key, hash_t>;

protected:

    hash_t hash_func(Key const &data) const {
        return _HashFunc::get(data, capacity());
    }

public:
    virtual ~HashSet() = default;

    virtual void add_item(Key const&) = 0;

    virtual void add_item(Key &&) = 0;

    virtual void remove_item(Key const&) = 0;

    virtual size_t count() const = 0;
    
    virtual size_t capacity() const = 0;

    virtual bool empty() const = 0;
    
    virtual bool containing(Key const&) const = 0;

    virtual Key& find(Key const&) = 0;

    virtual void clear() = 0;

    virtual void rehash(size_t) = 0;

    virtual void for_each(std::function<Key(Key const&)> const&) = 0;
};