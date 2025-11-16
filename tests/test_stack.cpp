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

TEST_F(StackTest, PushPopPeek) {
    stack_push(stack, "a");
    stack_push(stack, "b");
    EXPECT_EQ(stack_peek(stack), "b");
    EXPECT_NE(stack->top, nullptr);
    EXPECT_EQ(stack_pop(stack), "b");
    EXPECT_EQ(stack_peek(stack), "a");
    EXPECT_EQ(stack_pop(stack), "a");
    EXPECT_EQ(stack_peek(stack), "");
    EXPECT_EQ(stack_pop(stack), "");
    EXPECT_EQ(stack->top, nullptr);
}

TEST_F(StackTest, IsEmpty) {
    EXPECT_EQ(stack->top, nullptr);
    stack_push(stack, "q");
    EXPECT_NE(stack->top, nullptr);
    stack_pop(stack);
    EXPECT_EQ(stack->top, nullptr);
}

TEST_F(StackTest, Read) {
    stack_push(stack, "x");
    stack_push(stack, "y");
    EXPECT_EQ(stack_read(stack), "y x");
}

TEST_F(StackTest, PopEmpty) {
    EXPECT_EQ(stack_pop(stack), "");
    EXPECT_EQ(stack_peek(stack), "");
}

TEST_F(StackTest, BenchmarkPushPop) {
    for (int i = 0; i < 1000; ++i) {
        stack_push(stack, std::to_string(i));
    }
    int count = 0;
    while (stack->top != nullptr) {
        stack_pop(stack);
        count++;
    }
    EXPECT_EQ(count, 1000);
}
