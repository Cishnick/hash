#include <gtest/gtest.h>
#include "../src/chainhashset.hpp"

using Hash = ChainHashSet<std::string, Hash_Std>;


template <class Key, template<class T, template<class U,class V> class HashFunc> class Type>
HashSet<Type<Key, Hash_Std>, Key, Hash_Std>* createHashSet(size_t size) 
{
    return new Type<Key, Hash_Std>(size);
} 


TEST(HashTest, createCount) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    ASSERT_EQ(hash->count(), 0);

    delete hash;
}

TEST(HashTest, addCount) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    hash->add_item("Hello");

    ASSERT_EQ(hash->count(), 1);

    delete hash;
}

TEST(HashTest, add_rmCount) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    hash->add_item("Hello");
    hash->remove_item("Hello");

    ASSERT_EQ(hash->count(), 0);

    delete hash;
}

TEST(HashTest, containing) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    hash->add_item("Hello");
    hash->add_item("World");

    ASSERT_TRUE(hash->containing("World"));
    ASSERT_FALSE(hash->containing("I'm not existing"));  

    delete hash;  
}

TEST(HashTest, capacity) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);

    ASSERT_EQ(hash->capacity(), 10);
    delete hash;  
}

TEST(HashTest, replace) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);
    hash->add_item("Hello");
    hash->add_item("World");

    hash->replace("World", "People");
    
    ASSERT_TRUE(hash->containing("People"));
    ASSERT_FALSE(hash->containing("World"));

    delete hash;  
}

TEST(HashTest, for_each) {
    auto hash = createHashSet<std::string, ChainHashSet>(10);
    hash->add_item("Hello");
    hash->add_item("World");

    hash->for_each([](std::string const& val) {
        return val + '1';
    });
    
    ASSERT_TRUE(hash->containing("Hello1"));
    ASSERT_TRUE(hash->containing("World1"));
    ASSERT_FALSE(hash->containing("Hello"));
    ASSERT_FALSE(hash->containing("World"));
    
    delete hash;  
}