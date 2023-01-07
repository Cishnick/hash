#include <gtest/gtest.h>
#include "../src/doublehashset.hpp"

// using DHash = DoubleHashSet<std::string, Hash_Std, Hash_Div>;


TEST(DoubleHashTest, createCount) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);

    ASSERT_EQ(hash->count(), 0);

    delete hash;
}

TEST(DoubleHashTest, addCount) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);

    hash->add_item("Hello");

    ASSERT_EQ(hash->count(), 1);

    delete hash;
}

TEST(DoubleHashTest, add_rmCount) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);

    hash->add_item("Hello");
    hash->remove_item("Hello");

    ASSERT_EQ(hash->count(), 0);

    delete hash;
}

TEST(DoubleHashTest, containing) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);

    hash->add_item("Hello");
    hash->add_item("World");

    ASSERT_TRUE(hash->containing("World"));
    ASSERT_FALSE(hash->containing("I'm not existing"));  

    delete hash;  
}

TEST(DoubleHashTest, capacity) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);

    ASSERT_EQ(hash->capacity(), 32);
    delete hash;  
}

TEST(DoubleHashTest, replace) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    hash->add_item("Hello");
    hash->add_item("World");

    hash->replace("World", "People");
    
    ASSERT_TRUE(hash->containing("People"));
    ASSERT_FALSE(hash->containing("World"));

    delete hash;  
}

TEST(DoubleHashTest, for_each) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
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

TEST(DoubleHashTest, rehash) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    hash->add_item("Hello");
    hash->add_item("World");

    hash->rehash(6);
    
    ASSERT_TRUE(hash->containing("Hello"));
    ASSERT_TRUE(hash->containing("World"));
    ASSERT_EQ(hash->count(), 2);
    ASSERT_EQ(hash->capacity(), 64);
    
    delete hash;  
}

TEST(DoubleHashTest, copyconstr) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    
    hash->add_item("Hello");
    hash->add_item("World");

    auto chash(*hash);
    chash.rehash(6);
    
    ASSERT_TRUE(chash.containing("Hello"));
    ASSERT_TRUE(chash.containing("World"));
    ASSERT_EQ(chash.count(), 2);
    ASSERT_EQ(chash.capacity(), 64);
    ASSERT_EQ(hash->capacity(), 32);
    
    delete hash;  
}

TEST(DoubleHashTest, copyassign) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    
    hash->add_item("Hello");
    hash->add_item("World");

    auto chash = *hash;
    chash.rehash(6);

    ASSERT_TRUE(chash.containing("Hello"));
    ASSERT_TRUE(chash.containing("World"));
    ASSERT_EQ(chash.count(), 2);
    ASSERT_EQ(chash.capacity(), 64);
    ASSERT_EQ(hash->capacity(), 32);
    
    delete hash;  
}

TEST(DoubleHashTest, moveconstr) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    
    hash->add_item("Hello");
    hash->add_item("World");

    auto chash(std::move(*hash));
    
    ASSERT_TRUE(chash.containing("Hello"));
    ASSERT_TRUE(chash.containing("World"));
    ASSERT_EQ(chash.count(), 2);
    ASSERT_EQ(chash.capacity(), 32);
    ASSERT_EQ(hash->capacity(), 0);
    
    delete hash;  
}

TEST(DoubleHashTest, moveassign) {
    auto hash = new DoubleHashSet<std::string, Hash_Std, Hash_Div>(5);
    
    hash->add_item("Hello");
    hash->add_item("World");

    auto chash = std::move(*hash);
    
    ASSERT_TRUE(chash.containing("Hello"));
    ASSERT_TRUE(chash.containing("World"));
    ASSERT_EQ(chash.count(), 2);
    ASSERT_EQ(chash.capacity(), 32);
    ASSERT_EQ(hash->capacity(), 0);
    
    delete hash;  
}