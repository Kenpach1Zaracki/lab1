#include "storage.h"
#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "full_binary_tree.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Глобальные переменные для хранения всех структур
Entry entries[100];
int entryCount = 0;

// Поиск структуры по имени
Entry* find_entry(const std::string& name) {
    for (int i = 0; i < entryCount; i++) {
        if (entries[i].name == name) {
            return &entries[i];
        }
    }
    return nullptr;
}

// Сохранение всех структур в файл
void save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << " for writing" << std::endl;
        return;
    }
    
    for (int i = 0; i < entryCount; i++) {
        Entry& entry = entries[i];
        
        if (entry.type == "ARRAY") {
            Array* array = static_cast<Array*>(entry.ptr);
            file << "ARRAY " << array->name << " " << array_read(array) << std::endl;
        } 
        else if (entry.type == "FLIST") {
            Forward_List* list = static_cast<Forward_List*>(entry.ptr);
            file << "FLIST " << list->name << " " << flist_read(list) << std::endl;
        } 
        else if (entry.type == "DLIST") {
            Doubly_List* list = static_cast<Doubly_List*>(entry.ptr);
            file << "DLIST " << list->name << " " << dlist_read(list) << std::endl;
        } 
        else if (entry.type == "STACK") {
            Stack* stack = static_cast<Stack*>(entry.ptr);
            file << "STACK " << stack->name << " " << stack_read(stack) << std::endl;
        } 
        else if (entry.type == "QUEUE") {
            Queue* queue = static_cast<Queue*>(entry.ptr);
            file << "QUEUE " << queue->name << " " << queue_read(queue) << std::endl;
        } 
        else if (entry.type == "TREE") {
            Tree* tree = static_cast<Tree*>(entry.ptr);
            file << "TREE " << tree->name << " " << tree_read(tree) << std::endl;
        }
    }
    
    file.close();
}

// Загрузка структур из файла
void load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Info: File " << filename << " not found, starting with empty database" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, name;
        
        if (!(ss >> type >> name)) {
            continue; // Пропускаем некорректные строки
        }
        
        if (type == "ARRAY") {
            Array* array = create_array(name);
            std::string value;
            while (ss >> value) {
                array_push_back(array, value);
            }
            entries[entryCount++] = {"ARRAY", array, name};
        } 
        else if (type == "FLIST") {
            Forward_List* list = create_forward_list(name);
            std::string value;
            while (ss >> value) {
                flist_push_tail(list, value);
            }
            entries[entryCount++] = {"FLIST", list, name};
        } 
        else if (type == "DLIST") {
            Doubly_List* list = create_doubly_list(name);
            std::string value;
            while (ss >> value) {
                dlist_push_tail(list, value);
            }
            entries[entryCount++] = {"DLIST", list, name};
        } 
        else if (type == "STACK") {
            Stack* stack = create_stack(name);
            std::string value;
            std::string values[100];
            int count = 0;
            
            // Читаем все значения в массив
            while (ss >> value) {
                if (count < 100) {
                    values[count++] = value;
                }
            }
            
            // Пушим в обратном порядке для корректного LIFO
            for (int i = count - 1; i >= 0; i--) {
                stack_push(stack, values[i]);
            }
            
            entries[entryCount++] = {"STACK", stack, name};
        } 
        else if (type == "QUEUE") {
            Queue* queue = create_queue(name);
            std::string value;
            while (ss >> value) {
                queue_push(queue, value);
            }
            entries[entryCount++] = {"QUEUE", queue, name};
        } 
        else if (type == "TREE") {
            Tree* tree = create_tree(name);
            std::string value;
            while (ss >> value) {
                tree_insert(tree, value);
            }
            entries[entryCount++] = {"TREE", tree, name};
        }
    }
    
    file.close();
}

// Очистка всех структур (дополнительная функция)
void cleanup_storage() {
    for (int i = 0; i < entryCount; i++) {
        Entry& entry = entries[i];
        
        if (entry.type == "ARRAY") {
            destroy_array(static_cast<Array*>(entry.ptr));
        } 
        else if (entry.type == "FLIST") {
            destroy_forward_list(static_cast<Forward_List*>(entry.ptr));
        } 
        else if (entry.type == "DLIST") {
            destroy_doubly_list(static_cast<Doubly_List*>(entry.ptr));
        } 
        else if (entry.type == "STACK") {
            destroy_stack(static_cast<Stack*>(entry.ptr));
        } 
        else if (entry.type == "QUEUE") {
            destroy_queue(static_cast<Queue*>(entry.ptr));
        } 
        else if (entry.type == "TREE") {
            destroy_tree(static_cast<Tree*>(entry.ptr));
        }
    }
    entryCount = 0;
}