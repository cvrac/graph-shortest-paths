#include "../Queue.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class QueueTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        QueueTest() {
            // You can do set-up work for each test here.


        }

        virtual ~QueueTest() {
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
        uint32_t hashsize;
        Queue q;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(QueueTest, QueueWorks) {
        EXPECT_TRUE(q.empty());
        uint32_t id = 5;
        q.push(id);
        EXPECT_FALSE(q.empty());
        EXPECT_FALSE(q.empty());
        id = 10;
        q.push(id);
        EXPECT_TRUE(q.size() == q.maxsize());
        EXPECT_TRUE(q.full());
        int size = q.maxsize();
        id = 10;
        q.push(id);
        EXPECT_FALSE(q.maxsize() == size);

    }

}  //
