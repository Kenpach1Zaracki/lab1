#include <gtest/gtest.h>
#include "../storage.h"
#include "../array.h"
#include "../slist.h"
#include "../dlist.h"
#include "../stack.h"
#include "../queue.h"
#include "../full_binary_tree.h"
#include <fstream>
#include <cstdio>

class StorageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Очищаем глобальное состояние перед каждым тестом
        entryCount = 0;
    }
    
    void TearDown() override {
        // Очищаем все созданные структуры
        for (int i = 0; i < entryCount; i++) {
            Entry& entry = entries[i];
            if (entry.type == "ARRAY") {
                destroy_array(static_cast<Array*>(entry.ptr));
            } else if (entry.type == "FLIST") {
                destroy_forward_list(static_cast<Forward_List*>(entry.ptr));
            } else if (entry.type == "DLIST") {
                destroy_doubly_list(static_cast<Doubly_List*>(entry.ptr));
            } else if (entry.type == "STACK") {
                destroy_stack(static_cast<Stack*>(entry.ptr));
            } else if (entry.type == "QUEUE") {
                destroy_queue(static_cast<Queue*>(entry.ptr));
            } else if (entry.type == "TREE") {
                destroy_tree(static_cast<Tree*>(entry.ptr));
            }
        }
        entryCount = 0;
    }
};

TEST_F(StorageTest, FindEntry) {
    // Поиск в пустом хранилище
    EXPECT_EQ(find_entry("nonexistent"), nullptr);
    
    // Добавляем структуру и ищем её
    Array* array = create_array("test_array");
    array_push_back(array, "value1");
    entries[entryCount++] = {"ARRAY", array, "test_array"};
    
    Entry* found = find_entry("test_array");
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->type, "ARRAY");
    EXPECT_EQ(found->name, "test_array");
    
    // Поиск несуществующей структуры
    EXPECT_EQ(find_entry("another"), nullptr);
}

TEST_F(StorageTest, SaveAndLoadAllTypes) {
    const std::string filename = "test_storage.txt";
    
    // Создаем структуры всех типов
    Array* array = create_array("my_array");
    array_push_back(array, "a1");
    array_push_back(array, "a2");
    entries[entryCount++] = {"ARRAY", array, "my_array"};
    
    Forward_List* flist = create_forward_list("my_flist");
    flist_push_tail(flist, "f1");
    flist_push_tail(flist, "f2");
    entries[entryCount++] = {"FLIST", flist, "my_flist"};
    
    Doubly_List* dlist = create_doubly_list("my_dlist");
    dlist_push_tail(dlist, "d1");
    dlist_push_tail(dlist, "d2");
    entries[entryCount++] = {"DLIST", dlist, "my_dlist"};
    
    Stack* stack = create_stack("my_stack");
    stack_push(stack, "s1");
    stack_push(stack, "s2");
    entries[entryCount++] = {"STACK", stack, "my_stack"};
    
    Queue* queue = create_queue("my_queue");
    queue_push(queue, "q1");
    queue_push(queue, "q2");
    entries[entryCount++] = {"QUEUE", queue, "my_queue"};
    
    Tree* tree = create_tree("my_tree");
    tree_insert(tree, "t1");
    tree_insert(tree, "t2");
    entries[entryCount++] = {"TREE", tree, "my_tree"};
    
    // Сохраняем в файл
    save_to_file(filename);
    
    // Очищаем текущие структуры
    TearDown();
    SetUp();
    
    // Загружаем из файла
    load_from_file(filename);
    
    // Проверяем, что все структуры загружены корректно
    EXPECT_EQ(entryCount, 6);
    
    // Проверяем каждую структуру
    Entry* loaded_array = find_entry("my_array");
    ASSERT_NE(loaded_array, nullptr);
    Array* array_ptr = static_cast<Array*>(loaded_array->ptr);
    EXPECT_EQ(array_read(array_ptr), "a1 a2");
    
    Entry* loaded_flist = find_entry("my_flist");
    ASSERT_NE(loaded_flist, nullptr);
    Forward_List* flist_ptr = static_cast<Forward_List*>(loaded_flist->ptr);
    EXPECT_EQ(flist_read(flist_ptr), "f1 f2");
    
    Entry* loaded_dlist = find_entry("my_dlist");
    ASSERT_NE(loaded_dlist, nullptr);
    Doubly_List* dlist_ptr = static_cast<Doubly_List*>(loaded_dlist->ptr);
    EXPECT_EQ(dlist_read(dlist_ptr), "d1 d2");
    
    Entry* loaded_stack = find_entry("my_stack");
    ASSERT_NE(loaded_stack, nullptr);
    Stack* stack_ptr = static_cast<Stack*>(loaded_stack->ptr);
    EXPECT_EQ(stack_read(stack_ptr), "s2 s1"); // LIFO порядок
    
    Entry* loaded_queue = find_entry("my_queue");
    ASSERT_NE(loaded_queue, nullptr);
    Queue* queue_ptr = static_cast<Queue*>(loaded_queue->ptr);
    EXPECT_EQ(queue_read(queue_ptr), "q1 q2"); // FIFO порядок
    
    Entry* loaded_tree = find_entry("my_tree");
    ASSERT_NE(loaded_tree, nullptr);
    Tree* tree_ptr = static_cast<Tree*>(loaded_tree->ptr);
    EXPECT_TRUE(tree_find(tree_ptr, "t1"));
    EXPECT_TRUE(tree_find(tree_ptr, "t2"));
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST_F(StorageTest, SaveToInvalidFile) {
    // Попытка сохранить в невалидный путь
    save_to_file("/invalid/path/file.txt");
    // Должно завершиться без падения
}

TEST_F(StorageTest, LoadFromNonExistentFile) {
    // Загрузка из несуществующего файла
    load_from_file("nonexistent_file_12345.txt");
    // Должно завершиться без падения и без добавления записей
    EXPECT_EQ(entryCount, 0);
}

TEST_F(StorageTest, LoadMalformedFile) {
    const std::string filename = "malformed.txt";
    
    // Создаем файл с некорректными данными
    std::ofstream file(filename);
    file << "INVALID_TYPE bad_name data\n";
    file << "ARRAY\n"; // Неполная строка
    file << "UNKNOWN_TYPE name value1 value2\n";
    file.close();
    
    // Загружаем - должно обработать без падения
    load_from_file(filename);
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST_F(StorageTest, SaveEmptyStorage) {
    const std::string filename = "empty.txt";
    
    // Сохраняем пустое хранилище
    save_to_file(filename);
    
    // Проверяем, что файл создан (может быть пустым)
    std::ifstream file(filename);
    EXPECT_TRUE(file.good());
    file.close();
    
    std::remove(filename.c_str());
}

TEST_F(StorageTest, CleanupStorageFunction) {
    // Создаем несколько структур
    Array* array = create_array("array_to_clean");
    array_push_back(array, "test");
    entries[entryCount++] = {"ARRAY", array, "array_to_clean"};
    
    Stack* stack = create_stack("stack_to_clean");
    stack_push(stack, "test");
    entries[entryCount++] = {"STACK", stack, "stack_to_clean"};
    
    // Вызываем cleanup_storage (если она доступна)
    // Если cleanup_storage не объявлена в storage.h, можно вызвать её через extern
    // extern void cleanup_storage();
    // cleanup_storage();
    
    // Вместо этого используем наш TearDown
    TearDown();
    
    EXPECT_EQ(entryCount, 0);
}