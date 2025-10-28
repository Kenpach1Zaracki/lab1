#include "dlist.h"
#include <stdexcept>
#include <iostream>

// Создание пустого двусвязного списка
Doubly_List* create_doubly_list(const std::string& name) {
    Doubly_List* list = new Doubly_List;
    list->name = name;
    list->head = list->tail = nullptr;
    return list;
}
// Добавление в начало
void dlist_push_head(Doubly_List* list, const std::string& value) {
    DListNode* newNode = new DListNode{value, nullptr, list->head};
    if (list->head) 
        list->head->prev = newNode;
    else 
        list->tail = newNode;
    list->head = newNode;
}
// Добавление в конец
void dlist_push_tail(Doubly_List* list, const std::string& value) {
    DListNode* newNode = new DListNode{value, list->tail, nullptr};
    
    if (list->tail) {
        list->tail->next = newNode;
    } else {
        // Если список пустой
        list->head = newNode;
    }
    list->tail = newNode;
}
void dlist_insert_before(Doubly_List* list, const std::string& target, const std::string& value) {
    DListNode* current = list->head;
    
    // Ищем target
    while (current && current->data != target) {
        current = current->next;
    }
    
    if (!current) {
        std::cout << "Error: Target '" << target << "' not found" << std::endl;
        return;
    }
    
    // Создаем новый узел
    DListNode* newNode = new DListNode{value, current->prev, current};
    
    // Обновляем связи
    if (current->prev) {
        current->prev->next = newNode;
    } else {
        list->head = newNode; // Новый становится головой
    }
    current->prev = newNode;
}

// Вставка ПОСЛЕ элемента с заданным значением - O(n)
void dlist_insert_after(Doubly_List* list, const std::string& target, const std::string& value) {
    if (!list->head) return;
    
    DListNode* current = list->head;
    while (current && current->data != target) {
        current = current->next;
    }
    
    if (!current) return; // Элемент не найден
    
    // Создаем новый узел
    DListNode* newNode = new DListNode{value, current, current->next};
    
    // Обновляем связи
    if (current->next) {
        current->next->prev = newNode;
    } else {
        list->tail = newNode; // Новый становится хвостом
    }
    current->next = newNode;
}

// Удаление элемента ПЕРЕД заданным значением - O(n)
void dlist_delete_before(Doubly_List* list, const std::string& target) {
    if (!list->head) return;
    
    DListNode* current = list->head;
    while (current && current->data != target) {
        current = current->next;
    }
    
    if (!current || !current->prev) return; // Элемент не найден или перед ним ничего нет
    
    DListNode* toDelete = current->prev;
    
    // Обновляем связи
    if (toDelete->prev) {
        toDelete->prev->next = current;
    } else {
        list->head = current; // Удаляем голову
    }
    current->prev = toDelete->prev;
    
    delete toDelete;
}

// Удаление элемента ПОСЛЕ заданного значения - O(n)
void dlist_delete_after(Doubly_List* list, const std::string& target) {
    if (!list->head) return;
    
    DListNode* current = list->head;
    while (current && current->data != target) {
        current = current->next;
    }
    
    if (!current || !current->next) return; // Элемент не найден или после него ничего нет
    
    DListNode* toDelete = current->next;
    
    // Обновляем связи
    if (toDelete->next) {
        toDelete->next->prev = current;
    } else {
        list->tail = current; // Удаляем хвост
    }
    current->next = toDelete->next;
    
    delete toDelete;
}
// Удаление из начала
void dlist_delete_head(Doubly_List* list) {
    if (!list->head) return;
    DListNode* temp = list->head;
    list->head = list->head->next;
    if (list->head) list->head->prev = nullptr;
    else list->tail = nullptr;
    delete temp;
}
// Удаление из конца
void dlist_delete_tail(Doubly_List* list) {
    if (!list->tail) return;
    DListNode* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = nullptr;
    else list->head = nullptr;
    delete temp;
}
// Удаление по значению
void dlist_delete_value(Doubly_List* list, const std::string& value) {
    DListNode* current = list->head;
    
    while (current) {
        if (current->data == value) {
            // Обновляем соседние узлы
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->head = current->next; // Удаляем голову
            }
            
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev; // Удаляем хвост
            }
            
            DListNode* toDelete = current;
            current = current->next;
            delete toDelete;
            return; // Удаляем только первое вхождение
        } else {
            current = current->next;
        }
    }
}
// Поиск элемента
bool dlist_find(const Doubly_List* list, const std::string& value) {
    DListNode* current = list->head;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}
// Чтение всех элементов
std::string dlist_read(const Doubly_List* list) {
    std::string result;
    DListNode* current = list->head;
    while (current) {
        if (!result.empty()) result += " ";
        result += current->data;
        current = current->next;
    }
    return result;
}

void destroy_doubly_list(Doubly_List* list) {
    DListNode* current = list->head;
    while (current) {
        DListNode* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}
