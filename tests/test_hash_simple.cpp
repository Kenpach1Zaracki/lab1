#include <gtest/gtest.h>
#include "../hash_simple.h"
#include <set>

class SimpleHashTest : public ::testing::Test {
protected:
    SimpleHashTable* ht;
    void SetUp() override {
        ht = createSimpleHashTable(101);
    }
    void TearDown() override {
        destroySimpleHashTable(ht);
    }
};

TEST_F(SimpleHashTest, InsertAndSearch) {
    EXPECT_TRUE(simpleHashInsert(ht, "alice", 5));
    EXPECT_TRUE(simpleHashInsert(ht, "bob", 10));
    EXPECT_EQ(simpleHashSearch(ht, "alice"), 5);
    EXPECT_EQ(simpleHashSearch(ht, "bob"), 10);
    EXPECT_EQ(simpleHashSearch(ht, "not_found"), -1);
}

TEST_F(SimpleHashTest, DuplicateKeyUpdate) {
    EXPECT_TRUE(simpleHashInsert(ht, "key", 42));
    EXPECT_EQ(simpleHashSearch(ht, "key"), 42);
    EXPECT_TRUE(simpleHashInsert(ht, "key", 99)); // update
    EXPECT_EQ(simpleHashSearch(ht, "key"), 99);
}

TEST_F(SimpleHashTest, DeleteKey) {
    simpleHashInsert(ht, "cat", 1);
    simpleHashInsert(ht, "dog", 2);
    EXPECT_TRUE(simpleHashDelete(ht, "cat"));
    EXPECT_EQ(simpleHashSearch(ht, "cat"), -1);
    EXPECT_FALSE(simpleHashDelete(ht, "cat")); // double delete
    EXPECT_TRUE(simpleHashDelete(ht, "dog"));
}

TEST_F(SimpleHashTest, EdgeCases) {
    EXPECT_FALSE(simpleHashInsert(ht, "", 10)); // empty key
    EXPECT_FALSE(simpleHashDelete(ht, ""));     // empty key
    EXPECT_EQ(simpleHashSearch(ht, ""), -1);    // empty key
}

TEST_F(SimpleHashTest, GetKeys) {
    simpleHashInsert(ht, "a", 1);
    simpleHashInsert(ht, "b", 2);
    simpleHashInsert(ht, "c", 3);
    std::string keys[10];
    int count = 0;
    simpleHashGetKeys(ht, keys, count);
    EXPECT_EQ(count, 3);
    std::set<std::string> keyset(keys, keys + count);
    EXPECT_TRUE(keyset.count("a"));
    EXPECT_TRUE(keyset.count("b"));
    EXPECT_TRUE(keyset.count("c"));
}

TEST_F(SimpleHashTest, SearchEmptyTable) {
    EXPECT_EQ(simpleHashSearch(ht, "xyz"), -1);
}

TEST_F(SimpleHashTest, BenchmarkInsert) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        simpleHashInsert(ht, "key" + std::to_string(i), i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Insert 1000 keys: " << dur.count() << " us\n";
}
