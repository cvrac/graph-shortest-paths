#include "../Buffer.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class BufferTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        BufferTest() {
            // You can do set-up work for each test here.
        }

        virtual ~BufferTest() {
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

        Buffer buffer;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(BufferTest, BufferWorks) {
    ASSERT_EQ(buffer.getMaxListNodes(), 1);

    EXPECT_EQ(buffer.getCurListNodes(), 0);
    ListNodePos list_node = buffer.allocNewNode();
    BufferFeedback feedback = buffer.insertNeighbor(list_node.pos, 5, false);
    EXPECT_FALSE(feedback.edge_exists);

    feedback = buffer.insertNeighbor(list_node.pos, 6, false);
    EXPECT_FALSE(feedback.edge_exists);

    feedback = buffer.insertNeighbor(list_node.pos, 7, false);
    EXPECT_FALSE(feedback.edge_exists);

    feedback = buffer.insertNeighbor(list_node.pos, 6, false);
    EXPECT_TRUE(feedback.edge_exists);

    feedback = buffer.insertNeighbor(list_node.pos, 8, true);
    EXPECT_FALSE(feedback.edge_exists);
    EXPECT_EQ(feedback.last_pos, 1);


    EXPECT_EQ(buffer.getTotalReallocs(), 1);
    EXPECT_EQ(buffer.getCurListNodes(), 2);
    EXPECT_EQ(buffer.getMaxListNodes(), 2);

}

}  // 