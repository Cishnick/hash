#include <gtest/gtest.h>
#include "../src/chainhashset.hpp"

using Hash = ChainHashSet<std::string, Hash_Std>;


template <class Key, template<class T, template<class U,class V> class HashFunc> class Type>
HashSet<Type<Key, Hash_Std>, Key, Hash_Std>* createHashSet(size_t size) 
{
    return new Type<Key, Hash_Std>(size);
} 


TEST(ChainHashTest, createCount) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    ASSERT_EQ(hash->count(), 0);

    delete hash;
}

// TEST(ChainHashTest, addCount) {
//     Hash hash(10);

//     hash.add_item("Hello");

//     ASSERT_EQ(hash.count(), 1);
// }

// TEST(ChainHashTest, add_rmCount) {
//     Hash hash(10);

//     hash.add_item("Hello");
//     hash.remove_item("Hello");

//     ASSERT_EQ(hash.count(), 0);
// }

// TEST(ChainHashTest, containing) {
//     Hash hash(10);

//     hash.add_item("Hello");
//     hash.add_item("World");

//     ASSERT_TRUE(hash.containing("World"));
//     ASSERT_FALSE(hash.containing("I'm not existing"));    
// }