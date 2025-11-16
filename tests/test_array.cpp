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
// ДОБАВЬ! EDGE/ERROR TESTЫ

TEST_F(ArrayTest, DestroyNull) {
    EXPECT_NO_THROW(destroy_array(nullptr));
}

TEST_F(ArrayTest, GetSetNullArray) {
    EXPECT_THROW(array_get(nullptr, 0), std::out_of_range);
    EXPECT_THROW(array_set(nullptr, 0, "fail"), std::out_of_range);
}

TEST_F(ArrayTest, InsertDeleteOutOfBounds) {
    Array* arr2 = create_array("extra");
    EXPECT_THROW(array_insert(arr2, 100, "bad"), std::out_of_range);
    EXPECT_THROW(array_delete(arr2, 100), std::out_of_range);
    destroy_array(arr2);
}
