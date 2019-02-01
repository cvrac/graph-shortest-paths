#include "../src/HashTable.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
    class HashTableTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        HashTableTest() : hashsize(2), ht(hashsize) {
            // You can do set-up work for each test here.


        }

        virtual ~HashTableTest() {
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
        HashTable<uint32_t> ht;
    };

// Tests that the Foo::Bar() method does Abc.
    TEST_F(HashTableTest, HashTableWorks) {
        uint32_t id = 5;
    EXPECT_FALSE(ht.search(id));
//    EXPECT_FALSE(ht.size() == 5);

    ht.insert(id);
    id = 10;
    EXPECT_FALSE(ht.search(id));
    id = 5;
    EXPECT_TRUE(ht.search(id));
//    EXPECT_TRUE(ht.size() == 1);
    ht.clear();
    EXPECT_FALSE(ht.search(id));
//    EXPECT_TRUE(ht.size() == 0);
    }

}  //
