#include <gtest/gtest.h>
#include <chrono>
#include "../full_binary_tree.h"

class FullBinaryTreeTest : public ::testing::Test {
protected:
    Tree* tree;

    void SetUp() override {
        tree = create_tree("test_tree");
    }

    void TearDown() override {
        destroy_tree(tree);
    }
};

// Тест создания дерева
TEST_F(FullBinaryTreeTest, CreateTree) {
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->name, "test_tree");
    EXPECT_EQ(tree->root, nullptr);
}

// Тест вставки одного элемента
TEST_F(FullBinaryTreeTest, InsertSingleElement) {
    tree_insert(tree, "10");
    EXPECT_NE(tree->root, nullptr);
    EXPECT_EQ(tree->root->data, "10");
    EXPECT_TRUE(tree_is_full(tree));
}

// Тест вставки нескольких элементов
TEST_F(FullBinaryTreeTest, InsertMultipleElements) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    tree_insert(tree, "70");
    
    EXPECT_TRUE(tree_find(tree, "50"));
    EXPECT_TRUE(tree_find(tree, "30"));
    EXPECT_TRUE(tree_find(tree, "70"));
    EXPECT_TRUE(tree_is_full(tree));
}

// Тест поиска существующих элементов
TEST_F(FullBinaryTreeTest, FindExistingElements) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    tree_insert(tree, "70");
    tree_insert(tree, "20");
    tree_insert(tree, "40");
    
    EXPECT_TRUE(tree_find(tree, "50"));
    EXPECT_TRUE(tree_find(tree, "30"));
    EXPECT_TRUE(tree_find(tree, "70"));
    EXPECT_TRUE(tree_find(tree, "20"));
    EXPECT_TRUE(tree_find(tree, "40"));
}

// Тест поиска несуществующих элементов
TEST_F(FullBinaryTreeTest, FindNonExistingElements) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    
    EXPECT_FALSE(tree_find(tree, "100"));
    EXPECT_FALSE(tree_find(tree, "10"));
}

// Тест поиска в пустом дереве
TEST_F(FullBinaryTreeTest, FindInEmptyTree) {
    EXPECT_FALSE(tree_find(tree, "50"));
}

// Тест проверки полноты дерева - пустое дерево
TEST_F(FullBinaryTreeTest, IsFullEmptyTree) {
    EXPECT_TRUE(tree_is_full(tree));
}

// Тест проверки полноты дерева - полное дерево из 3 элементов
TEST_F(FullBinaryTreeTest, IsFullThreeElements) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    tree_insert(tree, "70");
    EXPECT_TRUE(tree_is_full(tree));
}

// Тест проверки полноты дерева - неполное дерево
TEST_F(FullBinaryTreeTest, IsNotFullTree) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    EXPECT_FALSE(tree_is_full(tree));
}

// Тест чтения дерева
TEST_F(FullBinaryTreeTest, ReadTree) {
    tree_insert(tree, "50");
    tree_insert(tree, "30");
    tree_insert(tree, "70");
    
    std::string result = tree_read(tree);
    EXPECT_FALSE(result.empty());
}

// Тест чтения пустого дерева
TEST_F(FullBinaryTreeTest, ReadEmptyTree) {
    std::string result = tree_read(tree);
    EXPECT_TRUE(result.empty());
}

// Бенчмарк для вставки
TEST_F(FullBinaryTreeTest, BenchmarkInsert) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree_insert(tree, std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Insert 1000 elements: " << duration.count() << " microseconds" << std::endl;
}

// Бенчмарк для поиска
TEST_F(FullBinaryTreeTest, BenchmarkFind) {
    for (int i = 0; i < 1000; ++i) {
        tree_insert(tree, std::to_string(i));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree_find(tree, std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Find 1000 elements: " << duration.count() << " microseconds" << std::endl;
}
