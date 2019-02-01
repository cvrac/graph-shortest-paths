#include "../src/Buffer.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class BufferTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        BufferTest() : buffer(1) {
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

    uint32_t pos = buffer.allocNewNode();
    long last_pos;
    bool feedback = buffer.insertNeighbor(pos, 5, 'S', 0, false, &last_pos);
    EXPECT_TRUE(feedback);

    feedback = buffer.insertNeighbor(pos, 6, 'S', 0, false, &last_pos);
    EXPECT_TRUE(feedback);

    feedback = buffer.insertNeighbor(pos, 7, 'S', 0, false, &last_pos);
    EXPECT_TRUE(feedback);

    feedback = buffer.insertNeighbor(pos, 6, 'S', 0, false, &last_pos);
    EXPECT_FALSE(feedback);

    feedback = buffer.insertNeighbor(pos, 8, 'S', 0, false, &last_pos);
    EXPECT_TRUE(feedback);
    EXPECT_EQ(last_pos, 1);

    feedback = buffer.insertNeighbor(last_pos, 9, 'S', 0, true, &last_pos);
    EXPECT_TRUE(feedback);

    feedback = buffer.insertNeighbor(pos, 9, 'S', 0, false, &last_pos);
    EXPECT_FALSE(feedback);

    EXPECT_EQ(buffer.getTotalReallocs(), 1);
    EXPECT_EQ(buffer.getCurListNodes(), 2);
    EXPECT_EQ(buffer.getMaxListNodes(), 2);

}

}  // 