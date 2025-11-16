#include <gtest/gtest.h>
#include "full_binary_tree.h" // Assuming this includes the Full Binary Tree implementation

class FullBinaryTreeTest : public ::testing::Test {
protected:
    FullBinaryTree<int> *tree;

    void SetUp() override {
        tree = new FullBinaryTree<int>();
    }

    void TearDown() override {
        delete tree;
    }
};

TEST_F(FullBinaryTreeTest, CreateTree) {
    EXPECT_TRUE(tree->is_empty());
}

TEST_F(FullBinaryTreeTest, InsertSingleNode) {
    tree->insert(1);
    EXPECT_FALSE(tree->is_empty());
    EXPECT_EQ(tree->find(1), 1);
}

TEST_F(FullBinaryTreeTest, InsertMultipleNodes) {
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    EXPECT_EQ(tree->find(2), 2);
    EXPECT_EQ(tree->find(3), 3);
}

TEST_F(FullBinaryTreeTest, IsFullForSingleNode) {
    tree->insert(1);
    EXPECT_TRUE(tree->is_full());
}

TEST_F(FullBinaryTreeTest, IsFullForFullBinaryTree) {
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    EXPECT_TRUE(tree->is_full());
}

TEST_F(FullBinaryTreeTest, IsFullForNonFullBinaryTree) {
    tree->insert(1);
    tree->insert(2);
    // Intentionally not inserting the third node to test non-full condition
    EXPECT_FALSE(tree->is_full());
}

TEST_F(FullBinaryTreeTest, FindInEmptyTree) {
    EXPECT_EQ(tree->find(99), -1); // Assuming -1 is the indicator for not found
}

TEST_F(FullBinaryTreeTest, BenchmarkInsert) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree->insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for insert: " << elapsed.count() << " seconds" << std::endl;
}

TEST_F(FullBinaryTreeTest, BenchmarkFind) {
    for (int i = 0; i < 1000; ++i) {
        tree->insert(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree->find(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for find: " << elapsed.count() << " seconds" << std::endl;
}