#include <iostream>
#include "chainhashset.hpp"


using Hash = ChainHashSet<std::string, Hash_Std>;

void display(Hash const& hash) {
    using namespace std;
    for(int i = 0; i != hash._capacity; ++i) {
        std::cout << i;
        for(auto const& x : hash.table[i]) {
            std::cout << " --> " << x;
        }
        std::cout << std::endl;
    }
    std::cout << "count: " << hash.count() << std::endl;
}


template <class Key, template<class T, template<class U,class V> class HashFunc> class Type>
HashSet<Type<Key, Hash_Std>, Key>* createHashSet(size_t size) 
{
    return new Type<Key, Hash_Std>(size);
} 


int main() {

    // std::vector<std::string> strs{
    //     "Hello world!", 
    //     "Hello dlrow!", 
    //     "Python is shit", 
    //     "Linux Manjaro",
    //     "Something else",
    //     "First try in hash tables"
    // };
    // Hash hash(10);

    // for(auto const& str : strs)
    //     hash.add_item(str);

    // display(hash);
    // std::cout << std::endl;
    
    // hash.for_each([](std::string const& val) {
    //     return val + '1';
    // });

    
    // auto chash(hash);
    
    // std::cout << chash.count() << std::endl;

    // display(chash);


    auto hash = static_cast<Hash*>(createHashSet<std::string, ChainHashSet>(10));
    
    hash->add_item("Hello");
    hash->add_item("World");

    auto chash(*hash);
    
    auto count = chash.capacity();

    display(chash);
    // auto count = hash->count();

    delete hash;  

    return 0;
}