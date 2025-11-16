#include <gtest/gtest.h>
#include "../array.h"

class ArrayTest : public ::testing::Test {
protected:
    Array* arr;
    void SetUp() override {
        arr = create_array("test_array");
    }
    void TearDown() override {
        destroy_array(arr);
    }
};

TEST_F(ArrayTest, CreateArray) {
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(array_length(arr), 0);
}

TEST_F(ArrayTest, PushBackAndGet) {
    array_push_back(arr, "a");
    array_push_back(arr, "b");
    EXPECT_EQ(array_length(arr), 2);
    EXPECT_EQ(array_get(arr, 0), "a");
    EXPECT_EQ(array_get(arr, 1), "b");
}

TEST_F(ArrayTest, InsertSetGet) {
    array_push_back(arr, "first");
    array_push_back(arr, "second");
    array_insert(arr, 1, "between");
    EXPECT_EQ(array_get(arr, 1), "between");
    array_set(arr, 1, "changed");
    EXPECT_EQ(array_get(arr, 1), "changed");
}

TEST_F(ArrayTest, Delete) {
    array_push_back(arr, "x");
    array_push_back(arr, "y");
    array_delete(arr, 0);
    EXPECT_EQ(array_length(arr), 1);
    EXPECT_EQ(array_get(arr, 0), "y");
}

TEST_F(ArrayTest, OutOfBounds) {
    EXPECT_THROW(array_get(arr, 5), std::out_of_range);
    EXPECT_THROW(array_set(arr, 3, "z"), std::out_of_range);
}

TEST_F(ArrayTest, Read) {
    array_push_back(arr, "hello");
    array_push_back(arr, "world");
    EXPECT_EQ(array_read(arr), "hello world");
}
