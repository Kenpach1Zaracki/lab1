#ifndef DLIST_H
#define DLIST_H

#include <string>

struct DListNode {
    std::string data;
    DListNode* prev;
    DListNode* next;
};

struct Doubly_List {
    std::string name;
    DListNode* head;
    DListNode* tail;
};

// Основные операции
Doubly_List* create_doubly_list(const std::string& name);
void dlist_push_head(Doubly_List* list, const std::string& value);
void dlist_push_tail(Doubly_List* list, const std::string& value);

// Новые операции для вставки и удаления
void dlist_insert_before(Doubly_List* list, const std::string& target, const std::string& value);
void dlist_insert_after(Doubly_List* list, const std::string& target, const std::string& value);
void dlist_delete_before(Doubly_List* list, const std::string& target);
void dlist_delete_after(Doubly_List* list, const std::string& target);

// Существующие операции
void dlist_delete_head(Doubly_List* list);
void dlist_delete_tail(Doubly_List* list);
void dlist_delete_value(Doubly_List* list, const std::string& value);
bool dlist_find(const Doubly_List* list, const std::string& value);
std::string dlist_read(const Doubly_List* list);
void destroy_doubly_list(Doubly_List* list);

#endif