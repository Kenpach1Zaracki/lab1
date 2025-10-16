#include "slist.h"
#include <stdexcept>

// Создание пустого списка
Forward_List* create_forward_list(const std::string& name) {
    Forward_List* list = new Forward_List;
    list->name = name;
    list->head = list->tail = nullptr;
    return list;
}
// Добавление в начало
void flist_push_head(Forward_List* list, const std::string& value) {
    SListNode* newNode = new SListNode{value, list->head};
    list->head = newNode;
    if (!list->tail) list->tail = newNode;
}
// Добавление в конец
void flist_push_tail(Forward_List* list, const std::string& value) {
    SListNode* newNode = new SListNode{value, nullptr};
    if (list->tail) list->tail->next = newNode;
    else list->head = newNode;
    list->tail = newNode;
}
void flist_insert_before(Forward_List* list, const std::string& target, const std::string& value) {
    if (!list->head) return; // Список пуст
    
    // Если target в голове, то вставляем в начало
    if (list->head->data == target) {
        flist_push_head(list, value);
        return;
    }
    
    // Ищем элемент перед target
    SListNode* current = list->head;
    while (current->next && current->next->data != target) {
        current = current->next;
    }
    
    // Если нашли target, вставляем перед ним
    if (current->next && current->next->data == target) {
        SListNode* newNode = new SListNode{value, current->next};
        current->next = newNode;
    }
}

// Вставка ПОСЛЕ элемента 
void flist_insert_after(Forward_List* list, const std::string& target, const std::string& value) {
    SListNode* current = list->head;
    
    // Ищем элемент target
    while (current && current->data != target) {
        current = current->next;
    }
    
    // Если нашли target, вставляем после него
    if (current) {
        SListNode* newNode = new SListNode{value, current->next};
        current->next = newNode;
        
        // Если вставили после хвоста, обновляем tail
        if (current == list->tail) {
            list->tail = newNode;
        }
    }
}

// Удаление элемента ПЕРЕД заданным значением - O(n)
void flist_delete_before(Forward_List* list, const std::string& target) {
    if (!list->head || !list->head->next) return; // Мало элементов
    
    // Если target второй элемент, удаляем голову
    if (list->head->next->data == target) {
        flist_delete_head(list);
        return;
    }
    
    // Ищем элемент за два до target
    SListNode* current = list->head;
    while (current->next && current->next->next && current->next->next->data != target) {
        current = current->next;
    }
    
    // Если нашли, удаляем элемент перед target
    if (current->next && current->next->next && current->next->next->data == target) {
        SListNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

// Удаление элемента ПОСЛЕ заданного значения - O(n)
void flist_delete_after(Forward_List* list, const std::string& target) {
    SListNode* current = list->head;
    
    // Ищем элемент target
    while (current && current->data != target) {
        current = current->next;
    }
    
    // Если нашли target и после него есть элемент
    if (current && current->next) {
        SListNode* temp = current->next;
        current->next = temp->next;
        
        // Если удалили хвост, обновляем tail
        if (temp == list->tail) {
            list->tail = current;
        }
        delete temp;
    }
}
// Удаление из начала
void flist_delete_head(Forward_List* list) {
    if (!list->head) return;
    SListNode* temp = list->head;
    list->head = list->head->next;
    if (!list->head) list->tail = nullptr;
    delete temp;
}
// Удаление из конца
void flist_delete_tail(Forward_List* list) {
    if (!list->head) return;
    if (list->head == list->tail) {
        delete list->head;
        list->head = list->tail = nullptr;
        return;
    }
    SListNode* current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    delete list->tail;
    current->next = nullptr;
    list->tail = current;
}
// Удаление по значению
void flist_delete_value(Forward_List* list, const std::string& value) {
    if (!list->head) return;
    if (list->head->data == value) {
        flist_delete_head(list);
        return;
    }
    SListNode* current = list->head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }
    if (current->next) {
        SListNode* temp = current->next;
        current->next = temp->next;
        if (temp == list->tail) list->tail = current;
        delete temp;
    }
}
// Поиск элемента
bool flist_find(const Forward_List* list, const std::string& value) {
    SListNode* current = list->head;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}
// Чтение всех элементов
std::string flist_read(const Forward_List* list) {
    std::string result;
    SListNode* current = list->head;
    while (current) {
        if (!result.empty()) result += " ";
        result += current->data;
        current = current->next;
    }
    return result;
}

void destroy_forward_list(Forward_List* list) {
    SListNode* current = list->head;
    while (current) {
        SListNode* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}
