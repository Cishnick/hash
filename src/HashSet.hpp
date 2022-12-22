#pragma once


template<class Key, template<class U,class V> class HashFunc>
class HashSet {
protected:
    using hash_t = size_t;
    using _HashFunc = HashFunc<T, hash_t>;

public:
    virtual ~HashSet() = default;

    virtual void add_item(Key const&) = 0;

    virtual void add_item(Key &&) = 0;

    virtual void remove_item(Key const&) = 0;

    virtual size_t count() const = 0;
    
    virtual size_t max_size() const = 0;

    virtual bool containing() const = 0;

    virtual bool find(Key const&) const = 0;

    virtual bool empty() const = 0;

    virtual void clear() = 0;

    virtual void rehash(size_t) = 0;
};