#include "../src/Garray.hpp"
#include "gtest/gtest.h"

using namespace std;

namespace {

// The fixture for testing class Foo.
    class ArrayTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        ArrayTest() : queue(2), stack(2) {
            // You can do set-up work for each test here.
        }

        virtual ~ArrayTest() {
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

        Garray<int> queue;
        Garray<int> stack;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(ArrayTest, QueueWorks) {
    ASSERT_EQ(queue.getSize(), 2);
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getHead(), 0);
    EXPECT_EQ(queue.getTail(), 0);
    EXPECT_EQ(queue.getElements(), 0);


    queue.enqueue(10);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 2);
    EXPECT_EQ(queue.getHead(), 0);
    EXPECT_EQ(queue.getTail(), 1);
    EXPECT_EQ(queue.getElements(), 1);

    queue.enqueue(20);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 2);
    EXPECT_EQ(queue.getHead(), 0);
    EXPECT_EQ(queue.getTail(), 0);
    EXPECT_EQ(queue.getElements(), 2);


    queue.enqueue(30);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    ASSERT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 0);
    EXPECT_EQ(queue.getTail(), 3);
    EXPECT_EQ(queue.getElements(), 3);


    int n = queue.popFront();
    EXPECT_EQ(n, 10);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 1);
    EXPECT_EQ(queue.getTail(), 3);
    EXPECT_EQ(queue.getElements(), 2);


    n = queue.popFront();
    EXPECT_EQ(n, 20);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 2);
    EXPECT_EQ(queue.getTail(), 3);
    EXPECT_EQ(queue.getElements(), 1);

    queue.enqueue(40);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 2);
    EXPECT_EQ(queue.getTail(), 0);
    EXPECT_EQ(queue.getElements(), 2);

    queue.enqueue(50);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 2);
    EXPECT_EQ(queue.getTail(), 1);
    EXPECT_EQ(queue.getElements(), 3);

    queue.enqueue(60);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 4);
    EXPECT_EQ(queue.getHead(), 2);
    EXPECT_EQ(queue.getTail(), 2);
    EXPECT_EQ(queue.getElements(), 4);


    queue.enqueue(70);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 2);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 5);

    n = queue.popFront();
    EXPECT_EQ(n, 30);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 3);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 4);

    n = queue.popFront();
    EXPECT_EQ(n, 40);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 4);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 3);


    n = queue.popFront();
    EXPECT_EQ(n, 50);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 5);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 2);

    n = queue.popFront();
    EXPECT_EQ(n, 60);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 6);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 1);

    n = queue.popFront();
    EXPECT_EQ(n, 70);
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.getSize(), 8);
    EXPECT_EQ(queue.getHead(), 7);
    EXPECT_EQ(queue.getTail(), 7);
    EXPECT_EQ(queue.getElements(), 0);

}

    TEST_F(ArrayTest, StackWorks) {
    ASSERT_EQ(stack.getSize(), 2);
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 0);
    EXPECT_EQ(stack.getElements(), 0);
    
    
    stack.enstack(10);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 2);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 1);
    EXPECT_EQ(stack.getElements(), 1);
    
    stack.enstack(20);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 2);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 2);
    EXPECT_EQ(stack.getElements(), 2);
    
    
    stack.enstack(30);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    ASSERT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 3);
    EXPECT_EQ(stack.getElements(), 3);
    
    
    int n = stack.popBack();
    EXPECT_EQ(n, 30);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 2);
    EXPECT_EQ(stack.getElements(), 2);
    
    
    n = stack.popBack();
    EXPECT_EQ(n, 20);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 1);
    EXPECT_EQ(stack.getElements(), 1);
    
    stack.enstack(40);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 2);
    EXPECT_EQ(stack.getElements(), 2);
    
    stack.enstack(50);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 3);
    EXPECT_EQ(stack.getElements(), 3);
    
    stack.enstack(60);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 4);
    EXPECT_EQ(stack.getElements(), 4);
    
    
    stack.enstack(70);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 5);
    EXPECT_EQ(stack.getElements(), 5);
    
    n = stack.popBack();
    EXPECT_EQ(n, 70);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 4);
    EXPECT_EQ(stack.getElements(), 4);
    
    n = stack.popBack();
    EXPECT_EQ(n, 60);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 3);
    EXPECT_EQ(stack.getElements(), 3);
    
    
    n = stack.popBack();
    EXPECT_EQ(n, 50);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 2);
    EXPECT_EQ(stack.getElements(), 2);
    
    n = stack.popBack();
    EXPECT_EQ(n, 40);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 1);
    EXPECT_EQ(stack.getElements(), 1);
    
    n = stack.popBack();
    EXPECT_EQ(n, 10);
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.getSize(), 8);
    EXPECT_EQ(stack.getHead(), 0);
    EXPECT_EQ(stack.getTail(), 0);
    EXPECT_EQ(stack.getElements(), 0);
    
    }

}  //
