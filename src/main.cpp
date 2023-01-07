#include <iostream>
#include "chainhashset.hpp"
#include "doublehashset.hpp"


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

using DHash = DoubleHashSet<std::string, Hash_Std, Hash_Div>;

void display(DHash const& hash) {
    using namespace std;
    for(int i = 0; i != hash._capacity; ++i) {
        std::cout << i;
        std::cout << ' ' << hash.table[i].data << ' ' << hash.table[i].deleted;
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


    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(4);
    
    hash->add_item("Hello");
    hash->add_item("World");

    hash->replace("World", "People");


    // std::vector<std::string> strs{
    //     "Hello world!", 
    //     "Hello dlrow!", 
    //     "Python is shit", 
    //     "Linux Manjaro",
    //     "Something else",
    //     "First try in hash tables"
    // };

    // for(auto const& str : strs)
    //     hash->add_item(str);

    // hash->replace("Hello world!", "Hello world!!!");
    auto chash(*hash);    

    std::cout << "del: " << hash->containing("World") << std::endl;

    delete hash;  
    display(chash);


    return 0;
}