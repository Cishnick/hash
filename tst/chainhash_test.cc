#include <gtest/gtest.h>
#include "../src/chainhash.hpp"


TEST(ChainHashTest, createCount) {
    ChainHash hash(10);

    ASSERT_EQ(hash.count(), 0);
}