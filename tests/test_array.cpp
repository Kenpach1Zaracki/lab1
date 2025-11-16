#include <gtest/gtest.h>
#include "../array.h"

class ArrayTest : public ::testing::Test {
protected:
    Array* arr;
    void SetUp() override {
        arr = array_create(10);
    }
    void TearDown() override {
        array_destroy(arr);
    }
};

TEST_F(ArrayTest, CreateArray) {
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(array_size(arr), 10);
}

TEST_F(ArrayTest, SetAndGet) {
    array_set(arr, 0, "a");
    array_set(arr, 5, "hello");
    EXPECT_EQ(array_get(arr, 0), "a");
    EXPECT_EQ(array_get(arr, 5), "hello");
    EXPECT_EQ(array_get(arr, 9), "");
}

TEST_F(ArrayTest, OutOfBoundsGetSet) {
    EXPECT_EQ(array_get(arr, 100), "");
    array_set(arr, 100, "z");
    EXPECT_EQ(array_get(arr, 100), "");
}
