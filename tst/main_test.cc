#include <gtest/gtest.h>
#include "base_test.h"
#include "chainhash_test.h"



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}