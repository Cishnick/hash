#pragma once
#include <functional>

template<class Impl, class Key, template<class U,class V> class HashFunc>
class HashSet {
protected:
    using hash_t = size_t;
    
private:

    using _HashFunc = HashFunc<Key, hash_t>;

    inline Impl* impl() {
        return static_cast<Impl*>(this);
    }

    inline const Impl* impl() const{
        return static_cast<const Impl*>(this);
    }

protected:
    hash_t hash_func(Key const &data) const {
        return _HashFunc::get(data, capacity());
    }

public:
    virtual ~HashSet() = default;

    void add_item(Key const& val) {
        impl()->add_item_impl(val);
    }

    void add_item(Key &&val) {
        impl()->add_item_impl(std::forward<Key>(val));
    }

    void remove_item(Key const& val) {
        impl()->remove_item_impl(val);
    }

    size_t count() const {
        return impl()->count_impl();
    }
    
    size_t capacity() const{
        return impl()->capacity_impl();
    }

    bool empty() const {
        return impl()->empty_impl();
    }
    
    bool containing(Key const& val) const {
        return impl()->containing_impl(val);
    }

    Key& find(Key const& val) {
        return impl()->find_impl(val);
    }

    void clear() {
        return impl()->clear_impl();
    }

    void rehash(size_t size) {
        impl()->rehash_impl(size);
    }

    void for_each(std::function<Key(Key const&)> const& func) {
        impl()->for_each_impl(func);
    }
};
