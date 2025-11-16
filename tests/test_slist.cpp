#include <gtest/gtest.h>
#include "../slist.h"

class ForwardListTest : public ::testing::Test {
protected:
    Forward_List* list;
    void SetUp() override {
        list = create_forward_list("test_slist");
    }
    void TearDown() override {
        destroy_forward_list(list);
    }
};

// Тесты добавления
TEST_F(ForwardListTest, PushHeadTail) {
    flist_push_head(list, "a");
    flist_push_tail(list, "b");
    EXPECT_TRUE(flist_find(list, "a"));
    EXPECT_TRUE(flist_find(list, "b"));
    EXPECT_EQ(flist_read(list), "a b");
}

TEST_F(ForwardListTest, InsertBeforeAfter) {
    flist_push_head(list, "a");
    flist_insert_after(list, "a", "b");
    flist_insert_before(list, "b", "c");
    EXPECT_EQ(flist_read(list), "a c b");
}

TEST_F(ForwardListTest, DeleteBeforeAfter) {
    flist_push_head(list, "1");
    flist_push_tail(list, "2");
    flist_push_tail(list, "3");
    // список: 1 2 3
    flist_delete_before(list, "3"); // удалит 2
    EXPECT_FALSE(flist_find(list, "2"));
    flist_delete_after(list, "1"); // удалит 3
    EXPECT_FALSE(flist_find(list, "3"));
}

TEST_F(ForwardListTest, DeleteHeadTailValue) {
    flist_push_head(list, "x");
    flist_push_tail(list, "y");
    flist_push_tail(list, "z");
    flist_delete_head(list);
    EXPECT_FALSE(flist_find(list, "x"));
    flist_delete_tail(list);
    EXPECT_FALSE(flist_find(list, "z"));
    flist_delete_value(list, "y");
    EXPECT_FALSE(flist_find(list, "y"));
}

TEST_F(ForwardListTest, FindRead) {
    flist_push_head(list, "k");
    flist_push_tail(list, "l");
    EXPECT_TRUE(flist_find(list, "k"));
    EXPECT_EQ(flist_read(list), "k l");
}

TEST_F(ForwardListTest, EmptyListOps) {
    flist_delete_head(list); // ничего не сломается
    flist_delete_tail(list);
    flist_delete_value(list, "notfound");
    EXPECT_FALSE(flist_find(list, "notfound"));
    EXPECT_EQ(flist_read(list), "");
}

TEST_F(ForwardListTest, BenchmarkInsertFind) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        flist_push_tail(list, std::to_string(i));
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(flist_find(list, std::to_string(i)));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur_insert = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
    auto dur_find = std::chrono::duration_cast<std::chrono::microseconds>(end - mid);
    std::cout << "Insert 1000: " << dur_insert.count() << " us, Find 1000: " << dur_find.count() << " us\n";
}
