#include <gtest/gtest.h>
#include "../stack.h"

class StackTest : public ::testing::Test {
protected:
    Stack* stack;
    void SetUp() override {
        stack = create_stack("test_stack");
    }
    void TearDown() override {
        destroy_stack(stack);
    }
};

TEST_F(StackTest, PushPopTop) {
    stack_push(stack, "a");
    stack_push(stack, "b");
    EXPECT_EQ(stack_top(stack), "b");
    EXPECT_FALSE(stack_is_empty(stack));
    stack_pop(stack);
    EXPECT_EQ(stack_top(stack), "a");
    stack_pop(stack);
    EXPECT_TRUE(stack_is_empty(stack));
}

TEST_F(StackTest, IsEmptySize) {
    EXPECT_TRUE(stack_is_empty(stack));
    EXPECT_EQ(stack_size(stack), 0);
    stack_push(stack, "q");
    EXPECT_EQ(stack_size(stack), 1);
}

TEST_F(StackTest, Find) {
    stack_push(stack, "x");
    stack_push(stack, "y");
    EXPECT_TRUE(stack_find(stack, "x"));
    EXPECT_FALSE(stack_find(stack, "notfound"));
}

TEST_F(StackTest, Read) {
    stack_push(stack, "z");
    stack_push(stack, "q");
    EXPECT_EQ(stack_read(stack), "z q");
}

TEST_F(StackTest, PopEmpty) {
    stack_pop(stack); // nothing should happen
    EXPECT_TRUE(stack_is_empty(stack));
}

TEST_F(StackTest, BenchmarkPushPop) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        stack_push(stack, std::to_string(i));
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        stack_pop(stack);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur_push = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
    auto dur_pop = std::chrono::duration_cast<std::chrono::microseconds>(end - mid);
    std::cout << "Push 1000: " << dur_push.count() << " us, Pop 1000: " << dur_pop.count() << " us\n";
}
