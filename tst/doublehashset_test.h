// #include <gtest/gtest.h>
// #include "../src/doublehashset.hpp"

// using Hash = DoubleHashSet<std::string, Hash_Std>;

// template <class Key, template<class T, template<class U,class V> class HashFunc> class Type>
// HashSet<Type<Key, Hash_Std>, Key>* createHashSet(size_t size) 
// {
//     return new Type<Key, Hash_Std>(size);
// } 

// TEST(HashTest, createCount) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);

//     ASSERT_EQ(hash->count(), 0);

//     delete hash;
// }

// TEST(HashTest, addCount) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);

//     hash->add_item("Hello");

//     ASSERT_EQ(hash->count(), 1);

//     delete hash;
// }

// TEST(HashTest, add_rmCount) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);

//     hash->add_item("Hello");
//     hash->remove_item("Hello");

//     ASSERT_EQ(hash->count(), 0);

//     delete hash;
// }

// TEST(HashTest, containing) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);

//     hash->add_item("Hello");
//     hash->add_item("World");

//     ASSERT_TRUE(hash->containing("World"));
//     ASSERT_FALSE(hash->containing("I'm not existing"));  

//     delete hash;  
// }

// TEST(HashTest, capacity) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);

//     ASSERT_EQ(hash->capacity(), 10);
//     delete hash;  
// }

// TEST(HashTest, replace) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);
//     hash->add_item("Hello");
//     hash->add_item("World");

//     hash->replace("World", "People");
    
//     ASSERT_TRUE(hash->containing("People"));
//     ASSERT_FALSE(hash->containing("World"));

//     delete hash;  
// }

// TEST(HashTest, for_each) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);
//     hash->add_item("Hello");
//     hash->add_item("World");

//     hash->for_each([](std::string const& val) {
//         return val + '1';
//     });
    
//     ASSERT_TRUE(hash->containing("Hello1"));
//     ASSERT_TRUE(hash->containing("World1"));
//     ASSERT_FALSE(hash->containing("Hello"));
//     ASSERT_FALSE(hash->containing("World"));
    
//     delete hash;  
// }

// TEST(HashTest, rehash) {
//     auto hash = createHashSet<std::string, DoubleHashSet>(10);
//     hash->add_item("Hello");
//     hash->add_item("World");

//     hash->rehash(15);
    
//     ASSERT_TRUE(hash->containing("Hello"));
//     ASSERT_TRUE(hash->containing("World"));
//     ASSERT_EQ(hash->count(), 2);
//     ASSERT_EQ(hash->capacity(), 15);
    
//     delete hash;  
// }

// TEST(HashTest, copyconstr) {
//     auto hash = static_cast<Hash*>(createHashSet<std::string, DoubleHashSet>(10));
    
//     hash->add_item("Hello");
//     hash->add_item("World");

//     auto chash(*hash);
//     chash.rehash(15);
    
//     ASSERT_TRUE(chash.containing("Hello"));
//     ASSERT_TRUE(chash.containing("World"));
//     ASSERT_EQ(chash.count(), 2);
//     ASSERT_EQ(chash.capacity(), 15);
//     ASSERT_EQ(hash->capacity(), 10);
    
//     delete hash;  
// }

// TEST(HashTest, copyassign) {
//     auto hash = static_cast<Hash*>(createHashSet<std::string, DoubleHashSet>(10));
    
//     hash->add_item("Hello");
//     hash->add_item("World");

//     auto chash = *hash;
//     chash.rehash(15);

//     ASSERT_TRUE(chash.containing("Hello"));
//     ASSERT_TRUE(chash.containing("World"));
//     ASSERT_EQ(chash.count(), 2);
//     ASSERT_EQ(chash.capacity(), 15);
//     ASSERT_EQ(hash->capacity(), 10);
    
//     delete hash;  
// }

// TEST(HashTest, moveconstr) {
//     auto hash = static_cast<Hash*>(createHashSet<std::string, DoubleHashSet>(10));
    
//     hash->add_item("Hello");
//     hash->add_item("World");

//     auto chash(std::move(*hash));
    
//     ASSERT_TRUE(chash.containing("Hello"));
//     ASSERT_TRUE(chash.containing("World"));
//     ASSERT_EQ(chash.count(), 2);
//     ASSERT_EQ(chash.capacity(), 10);
//     ASSERT_EQ(hash->capacity(), 0);
    
//     delete hash;  
// }

// TEST(HashTest, moveassign) {
//     auto hash = static_cast<Hash*>(createHashSet<std::string, DoubleHashSet>(10));
    
//     hash->add_item("Hello");
//     hash->add_item("World");

//     auto chash = std::move(*hash);
    
//     ASSERT_TRUE(chash.containing("Hello"));
//     ASSERT_TRUE(chash.containing("World"));
//     ASSERT_EQ(chash.count(), 2);
//     ASSERT_EQ(chash.capacity(), 10);
//     ASSERT_EQ(hash->capacity(), 0);
    
//     delete hash;  
// }