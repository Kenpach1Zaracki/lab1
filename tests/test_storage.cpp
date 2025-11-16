#include <gtest/gtest.h>
#include "../storage.h"

TEST(StorageTest, CreateDestroySmokeTest) {
    Storage* s = storage_create();
    ASSERT_NE(s, nullptr);
    storage_destroy(s);
}

TEST(StorageTest, DestroyNull) {
    EXPECT_NO_THROW(storage_destroy(nullptr));
}
