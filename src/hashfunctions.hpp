#pragma once
#include <string>
#include <algorithm>
#include <numeric>

template <class T, class U>
class Hash_Div {
public:
    explicit Hash_Div() = delete;

    static U get(T const& val, U size) {
        return val % size;
    }
};

template <class U>
class Hash_Div<std::string, U> {
public:
    explicit Hash_Div() = delete;

    static U get(std::string const& val, U size) {
        auto sum = static_cast<U>(std::accumulate(val.cbegin(), val.cend(), 0));
        return Hash_Div<U, U>::get(sum, size);
    }
};