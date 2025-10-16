#include "storage.h"
#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "avl_tree.h" 
#include <fstream>
#include <sstream>

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
    std::ofstream f(filename);
    if (!f.is_open()) return;
    
    for (int i = 0; i < entryCount; i++) {
        Entry e = entries[i];
        if (e.type == "ARRAY") {
            Array* a = (Array*)e.ptr;
            f << "ARRAY " << a->name << " " << array_read(a) << std::endl;
        } else if (e.type == "FLIST") {
            Forward_List* l = (Forward_List*)e.ptr;
            f << "FLIST " << l->name << " " << flist_read(l) << std::endl;
        } else if (e.type == "DLIST") {
            Doubly_List* l = (Doubly_List*)e.ptr;
            f << "DLIST " << l->name << " " << dlist_read(l) << std::endl;
        } else if (e.type == "STACK") {
            Stack* s = (Stack*)e.ptr;
            f << "STACK " << s->name << " " << stack_read(s) << std::endl;
        } else if (e.type == "QUEUE") {
            Queue* q = (Queue*)e.ptr;
            f << "QUEUE " << q->name << " " << queue_read(q) << std::endl;
        } else if (e.type == "TREE") {
            Tree* t = (Tree*)e.ptr;
            f << "TREE " << t->name << " " << tree_read(t) << std::endl;
        }
    }
    f.close();
}
// Загрузка структур из файла
void load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;
    
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string type, name;
        ss >> type >> name;
        
        if (type == "ARRAY") {
            Array* a = create_array(name);
            std::string val;
            while (ss >> val) {
                array_push_back(a, val);
            }
            entries[entryCount++] = {"ARRAY", a, name};
        } else if (type == "FLIST") {
            Forward_List* l = create_forward_list(name);
            std::string val;
            while (ss >> val) {
                flist_push_tail(l, val);
            }
            entries[entryCount++] = {"FLIST", l, name};
        } else if (type == "DLIST") {
            Doubly_List* l = create_doubly_list(name);
            std::string val;
            while (ss >> val) {
                dlist_push_tail(l, val);
            }
            entries[entryCount++] = {"DLIST", l, name};
        } else if (type == "STACK") {
            Stack* s = create_stack(name);
            std::string val;
            std::string values[100];
            int count = 0;
            
            // Сначала читаем все значения в массив
            while (ss >> val) {
                values[count++] = val;
            }
            
            // Пушим в обратном порядке (от последнего к первому)
            for (int i = count - 1; i >= 0; i--) {
                stack_push(s, values[i]);
            }
            
            entries[entryCount++] = {"STACK", s, name};
        } else if (type == "QUEUE") {
            Queue* q = create_queue(name);
            std::string val;
            while (ss >> val) {
                queue_push(q, val);
            }
            entries[entryCount++] = {"QUEUE", q, name};
        } else if (type == "TREE") {
            Tree* t = create_tree(name);
            std::string val;
            while (ss >> val) {
                tree_insert(t, val);
            }
            entries[entryCount++] = {"TREE", t, name};
        }
    }
    f.close();
}