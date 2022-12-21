#include <gtest/gtest.h>
#include "../src/chainhash.hpp"


TEST(ChainHashTest, createCount) {
    ChainHash hash(10);

    ASSERT_EQ(hash.count(), 0);
}

TEST(ChainHashTest, addCount) {
    ChainHash hash(10);

    hash.add_item("Hello");

    ASSERT_EQ(hash.count(), 1);
}

TEST(ChainHashTest, add_rmCount) {
    ChainHash hash(10);

    hash.add_item("Hello");
    hash.remove_item("Hello");

    ASSERT_EQ(hash.count(), 0);
}

TEST(ChainHashTest, containing) {
    ChainHash hash(10);

    hash.add_item("Hello");
    hash.add_item("World");

    ASSERT_TRUE(hash.containing("World"));
    ASSERT_FALSE(hash.containing("I'm not existing"));    
}