#include <gtest/gtest.h>
#include "../src/chainhash.hpp"

using Hash = ChainHash<std::string, Hash_Std>;

TEST(ChainHashTest, createCount) {
    Hash hash(10);

    ASSERT_EQ(hash.count(), 0);
}

TEST(ChainHashTest, addCount) {
    Hash hash(10);

    hash.add_item("Hello");

    ASSERT_EQ(hash.count(), 1);
}

TEST(ChainHashTest, add_rmCount) {
    Hash hash(10);

    hash.add_item("Hello");
    hash.remove_item("Hello");

    ASSERT_EQ(hash.count(), 0);
}

TEST(ChainHashTest, containing) {
    Hash hash(10);

    hash.add_item("Hello");
    hash.add_item("World");

    ASSERT_TRUE(hash.containing("World"));
    ASSERT_FALSE(hash.containing("I'm not existing"));    
}