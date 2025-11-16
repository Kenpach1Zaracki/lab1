#include <gtest/gtest.h>
#include "../dlist.h"

class DoublyListTest : public ::testing::Test {
protected:
    Doubly_List* list;
    void SetUp() override {
        list = create_doubly_list("test_dlist");
    }
    void TearDown() override {
        destroy_doubly_list(list);
    }
};

TEST_F(DoublyListTest, PushHeadTail) {
    dlist_push_head(list, "a");
    dlist_push_tail(list, "b");
    EXPECT_TRUE(dlist_find(list, "a"));
    EXPECT_TRUE(dlist_find(list, "b"));
    EXPECT_EQ(dlist_read(list), "a b");
}

TEST_F(DoublyListTest, InsertBeforeAfter) {
    dlist_push_head(list, "a");
    dlist_insert_after(list, "a", "b");
    dlist_insert_before(list, "b", "c");
    EXPECT_EQ(dlist_read(list), "a c b");
}

TEST_F(DoublyListTest, DeleteBeforeAfter) {
    dlist_push_head(list, "1");
    dlist_push_tail(list, "2");
    dlist_push_tail(list, "3");
    // список: 1 2 3
    dlist_delete_before(list, "3"); // удалит 2
    EXPECT_FALSE(dlist_find(list, "2"));
    dlist_delete_after(list, "1"); // удалит 3
    EXPECT_FALSE(dlist_find(list, "3"));
}

TEST_F(DoublyListTest, DeleteHeadTailValue) {
    dlist_push_head(list, "x");
    dlist_push_tail(list, "y");
    dlist_push_tail(list, "z");
    dlist_delete_head(list);
    EXPECT_FALSE(dlist_find(list, "x"));
    dlist_delete_tail(list);
    EXPECT_FALSE(dlist_find(list, "z"));
    dlist_delete_value(list, "y");
    EXPECT_FALSE(dlist_find(list, "y"));
}

TEST_F(DoublyListTest, FindRead) {
    dlist_push_head(list, "k");
    dlist_push_tail(list, "l");
    EXPECT_TRUE(dlist_find(list, "k"));
    EXPECT_EQ(dlist_read(list), "k l");
}

TEST_F(DoublyListTest, EmptyListOps) {
    dlist_delete_head(list); // безопасно
    dlist_delete_tail(list);
    dlist_delete_value(list, "notfound");
    EXPECT_FALSE(dlist_find(list, "notfound"));
    EXPECT_EQ(dlist_read(list), "");
}

TEST_F(DoublyListTest, BenchmarkInsertFind) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dlist_push_tail(list, std::to_string(i));
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(dlist_find(list, std::to_string(i)));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur_insert = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
    auto dur_find = std::chrono::duration_cast<std::chrono::microseconds>(end - mid);
    std::cout << "Insert 1000: " << dur_insert.count() << " us, Find 1000: " << dur_find.count() << " us\n";
}
