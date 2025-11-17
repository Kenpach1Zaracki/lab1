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
    // Проверяем, что операции на пустом списке бросают исключения
    EXPECT_THROW(flist_delete_head(list), std::runtime_error);
    EXPECT_THROW(flist_delete_tail(list), std::runtime_error);
    EXPECT_THROW(flist_delete_value(list, "value"), std::runtime_error);
    EXPECT_THROW(flist_insert_before(list, "target", "value"), std::runtime_error);
    EXPECT_THROW(flist_insert_after(list, "target", "value"), std::runtime_error);
    EXPECT_THROW(flist_delete_before(list, "target"), std::runtime_error);
    EXPECT_THROW(flist_delete_after(list, "target"), std::runtime_error);
    
    // Эти операции не должны бросать исключения на пустом списке
    EXPECT_FALSE(flist_find(list, "value"));
    EXPECT_EQ(flist_read(list), "");
}

TEST_F(ForwardListTest, EdgeCases) {
    // Тесты для граничных случаев используя фикстурный список
    EXPECT_THROW(flist_insert_before(list, "nonexistent", "value"), std::runtime_error);
    EXPECT_THROW(flist_insert_after(list, "nonexistent", "value"), std::runtime_error);
    EXPECT_THROW(flist_delete_before(list, "nonexistent"), std::runtime_error);
    EXPECT_THROW(flist_delete_after(list, "nonexistent"), std::runtime_error);
    
    // Добавим элементы и протестируем дополнительные edge cases
    flist_push_head(list, "first");
    flist_push_tail(list, "last");
    
    // Попытка вставить/удалить относительно несуществующих элементов
    EXPECT_THROW(flist_insert_before(list, "missing", "value"), std::runtime_error);
    EXPECT_THROW(flist_insert_after(list, "missing", "value"), std::runtime_error);
    EXPECT_THROW(flist_delete_before(list, "missing"), std::runtime_error);
    EXPECT_THROW(flist_delete_after(list, "missing"), std::runtime_error);
    
    // Особые случаи с первым и последним элементами
    EXPECT_THROW(flist_delete_before(list, "first"), std::runtime_error); // Нельзя удалить перед первым
    EXPECT_THROW(flist_delete_after(list, "last"), std::runtime_error);   // Нельзя удалить после последнего
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

// Отдельные тесты для особых случаев (не используют фикстуру)
TEST(SlistExtraTest, DestroyNull) {
    EXPECT_NO_THROW(destroy_forward_list(nullptr));
}

TEST(SlistExtraTest, PushNull) {
    EXPECT_THROW(flist_push_head(nullptr, "item"), std::invalid_argument);
    EXPECT_THROW(flist_push_tail(nullptr, "item"), std::invalid_argument);
}

TEST(SlistExtraTest, DeleteFindPopEmpty) {
    Forward_List* list = create_forward_list("extra");
    EXPECT_THROW(flist_delete_value(list, "notfound"), std::runtime_error);
    EXPECT_THROW(flist_delete_head(list), std::runtime_error);
    EXPECT_THROW(flist_delete_tail(list), std::runtime_error);
    EXPECT_FALSE(flist_find(list, "notfound"));
    destroy_forward_list(list);
}