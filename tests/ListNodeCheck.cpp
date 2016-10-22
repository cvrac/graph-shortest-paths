#include "../ListNode.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class ListNodeTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        ListNodeTest() {
            // You can do set-up work for each test here.
        }

        virtual ~ListNodeTest() {
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

        ListNode listNode;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(ListNodeTest, ListNodeWorks) {
    EXPECT_FALSE(listNode.search(10));
    EXPECT_FALSE(listNode.isFull());

    listNode.insertNeighbor(10);
    EXPECT_FALSE(listNode.isFull());
    EXPECT_FALSE(listNode.search(11));
    EXPECT_TRUE(listNode.search(10));

    listNode.insertNeighbor(11);
    EXPECT_FALSE(listNode.isFull());
    EXPECT_FALSE(listNode.search(12));
    EXPECT_TRUE(listNode.search(10));
    EXPECT_TRUE(listNode.search(11));

    listNode.insertNeighbor(12);
    EXPECT_TRUE(listNode.isFull());
    EXPECT_FALSE(listNode.search(13));
    EXPECT_TRUE(listNode.search(10));
    EXPECT_TRUE(listNode.search(11));
    EXPECT_TRUE(listNode.search(12));
}

}  // 