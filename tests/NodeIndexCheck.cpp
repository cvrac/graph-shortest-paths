#include "../src/NodeIndex.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class IndexTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        IndexTest() : index(3) {
            // You can do set-up work for each test here.
        }

        virtual ~IndexTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        NodeIndex index;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(IndexTest, IndexWorks) {
    ASSERT_EQ(index.getMaxSize(), 3);

    EXPECT_EQ(index.getCurSize(), 0);
    index.insertNode(2);
    EXPECT_EQ(index.getCurSize(), 3);

    index.insertNode(4);
    EXPECT_EQ(index.getTotalReallocs(), 1);
    EXPECT_EQ(index.getCurSize(), 5);
    EXPECT_EQ(index.getMaxSize(), 6);

}

}  //
