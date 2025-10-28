#ifndef SLIST_H
#define SLIST_H

#include <string>

struct SListNode {
    std::string data;
    SListNode* next;
};

struct Forward_List {
    std::string name;
    SListNode* head;
    SListNode* tail;
};

// Основные операции
Forward_List* create_forward_list(const std::string& name);
void flist_push_head(Forward_List* list, const std::string& value);
void flist_push_tail(Forward_List* list, const std::string& value);

void flist_insert_before(Forward_List* list, const std::string& target, const std::string& value);
void flist_insert_after(Forward_List* list, const std::string& target, const std::string& value);
void flist_delete_before(Forward_List* list, const std::string& target);
void flist_delete_after(Forward_List* list, const std::string& target);

void flist_delete_head(Forward_List* list);
void flist_delete_tail(Forward_List* list);
void flist_delete_value(Forward_List* list, const std::string& value);
bool flist_find(const Forward_List* list, const std::string& value);
std::string flist_read(const Forward_List* list);
void destroy_forward_list(Forward_List* list);

#endif