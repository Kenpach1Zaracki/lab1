#include "commands.h"
#include "storage.h"
#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "avl_tree.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

extern Entry entries[100];
extern int entryCount;

// Обработка всех команд
void process_command(const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    ss >> cmd;

    try {
        // ==================== КОМАНДЫ ДЛЯ МАССИВА ====================
        if (cmd == "MPUSH") {
            std::string name, val;
            int index;
            ss >> name >> index >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Array* a = create_array(name);
                array_insert(a, index, val);  // Используем вставку по индексу
                entries[entryCount++] = {"ARRAY", a, name};
            } else {
                array_insert((Array*)e->ptr, index, val);
            }
        } else if (cmd == "MSET") {
            std::string name, val;
            int index;
            ss >> name >> index >> val;
            Entry* e = find_entry(name);
            if (e) {
                array_set((Array*)e->ptr, index, val);
            }
        } else if (cmd == "MGET") {
            std::string name;
            int index;
            ss >> name >> index;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << array_get((Array*)e->ptr, index) << std::endl;
            }
        } else if (cmd == "MDEL") {
            std::string name;
            int index;
            ss >> name >> index;
            Entry* e = find_entry(name);
            if (e) {
                array_delete((Array*)e->ptr, index);
            }
        } else if (cmd == "MLEN") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                Array* a = (Array*)e->ptr;
                std::cout << array_length(a) << std::endl;
            }
        
        // ==================== КОМАНДЫ ДЛЯ ОДНОСВЯЗНОГО СПИСКА ====================
        } else if (cmd == "FPUSH_HEAD") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Forward_List* l = create_forward_list(name);
                flist_push_head(l, val);
                entries[entryCount++] = {"FLIST", l, name};
            } else {
                flist_push_head((Forward_List*)e->ptr, val);
            }
        } else if (cmd == "FPUSH_TAIL") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Forward_List* l = create_forward_list(name);
                flist_push_tail(l, val);
                entries[entryCount++] = {"FLIST", l, name};
            } else {
                flist_push_tail((Forward_List*)e->ptr, val);
            }
        } else if (cmd == "FINSERT_BEFORE") {
            std::string name, target, val;
            ss >> name >> target >> val;
            Entry* e = find_entry(name);
            if (e) {
                flist_insert_before((Forward_List*)e->ptr, target, val);
            }
        } else if (cmd == "FINSERT_AFTER") {
            std::string name, target, val;
            ss >> name >> target >> val;
            Entry* e = find_entry(name);
            if (e) {
                flist_insert_after((Forward_List*)e->ptr, target, val);
            }
        } else if (cmd == "FDEL_VAL") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (e) {
                flist_delete_value((Forward_List*)e->ptr, val);
            }
        } else if (cmd == "FDEL_HEAD") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                flist_delete_head((Forward_List*)e->ptr);
            }
        } else if (cmd == "FDEL_TAIL") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                flist_delete_tail((Forward_List*)e->ptr);
            }
        } else if (cmd == "FDEL_BEFORE") {
            std::string name, target;
            ss >> name >> target;
            Entry* e = find_entry(name);
            if (e) {
                flist_delete_before((Forward_List*)e->ptr, target);
            }
        } else if (cmd == "FDEL_AFTER") {
            std::string name, target;
            ss >> name >> target;
            Entry* e = find_entry(name);
            if (e) {
                flist_delete_after((Forward_List*)e->ptr, target);
            }
        } else if (cmd == "FGET") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (e && flist_find((Forward_List*)e->ptr, val)) {
                std::cout << "TRUE" << std::endl;
            } else {
                std::cout << "FALSE" << std::endl;
            }
        
        // ==================== КОМАНДЫ ДЛЯ ДВУСВЯЗНОГО СПИСКА ====================
        } else if (cmd == "LPUSH_HEAD") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Doubly_List* l = create_doubly_list(name);
                dlist_push_head(l, val);
                entries[entryCount++] = {"DLIST", l, name};
            } else {
                dlist_push_head((Doubly_List*)e->ptr, val);
            }
        } else if (cmd == "LPUSH_TAIL") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Doubly_List* l = create_doubly_list(name);
                dlist_push_tail(l, val);
                entries[entryCount++] = {"DLIST", l, name};
            } else {
                dlist_push_tail((Doubly_List*)e->ptr, val);
            }
        } else if (cmd == "LINSERT_BEFORE") {
            std::string name, target, val;
            ss >> name >> target >> val;
            Entry* e = find_entry(name);
            if (e) {
                dlist_insert_before((Doubly_List*)e->ptr, target, val);
            }
        } else if (cmd == "LINSERT_AFTER") {
            std::string name, target, val;
            ss >> name >> target >> val;
            Entry* e = find_entry(name);
            if (e) {
                dlist_insert_after((Doubly_List*)e->ptr, target, val);
            }
        } else if (cmd == "LDEL_VAL") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (e) {
                dlist_delete_value((Doubly_List*)e->ptr, val);
            }
        } else if (cmd == "LDEL_HEAD") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                dlist_delete_head((Doubly_List*)e->ptr);
            }
        } else if (cmd == "LDEL_TAIL") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                dlist_delete_tail((Doubly_List*)e->ptr);
            }
        } else if (cmd == "LDEL_BEFORE") {
            std::string name, target;
            ss >> name >> target;
            Entry* e = find_entry(name);
            if (e) {
                dlist_delete_before((Doubly_List*)e->ptr, target);
            }
        } else if (cmd == "LDEL_AFTER") {
            std::string name, target;
            ss >> name >> target;
            Entry* e = find_entry(name);
            if (e) {
                dlist_delete_after((Doubly_List*)e->ptr, target);
            }
        } else if (cmd == "LGET") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (e && dlist_find((Doubly_List*)e->ptr, val)) {
                std::cout << "TRUE" << std::endl;
            } else {
                std::cout << "FALSE" << std::endl;
            }
        
        // ==================== КОМАНДЫ ДЛЯ СТЕКА ====================
        } else if (cmd == "SPUSH") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Stack* s = create_stack(name);
                stack_push(s, val);
                entries[entryCount++] = {"STACK", s, name};
            } else {
                stack_push((Stack*)e->ptr, val);
            }
        } else if (cmd == "SPOP") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << stack_pop((Stack*)e->ptr) << std::endl;
            }
        } else if (cmd == "SPEEK") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << stack_peek((Stack*)e->ptr) << std::endl;
            }
        
        // ==================== КОМАНДЫ ДЛЯ ОЧЕРЕДИ ====================
        } else if (cmd == "QPUSH") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Queue* q = create_queue(name);
                queue_push(q, val);
                entries[entryCount++] = {"QUEUE", q, name};
            } else {
                queue_push((Queue*)e->ptr, val);
            }
        } else if (cmd == "QPOP") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << queue_pop((Queue*)e->ptr) << std::endl;
            }
        } else if (cmd == "QPEEK") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << queue_peek((Queue*)e->ptr) << std::endl;
            }
        
        // ==================== КОМАНДЫ ДЛЯ ДЕРЕВА ====================
        } else if (cmd == "TINSERT") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (!e) {
                Tree* t = create_tree(name);
                tree_insert(t, val);
                entries[entryCount++] = {"TREE", t, name};
            } else {
                tree_insert((Tree*)e->ptr, val);
            }
        } else if (cmd == "TISMEMBER") {
            std::string name, val;
            ss >> name >> val;
            Entry* e = find_entry(name);
            if (e && tree_find((Tree*)e->ptr, val)) {
                std::cout << "TRUE" << std::endl;
            } else {
                std::cout << "FALSE" << std::endl;
            }
        } else if (cmd == "TCHECKFULL") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e && tree_is_full(((Tree*)e->ptr)->root)) {
                std::cout << "TRUE" << std::endl;
            } else {
                std::cout << "FALSE" << std::endl;
            }
        } else if (cmd == "TGET") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (e) {
                std::cout << tree_read((Tree*)e->ptr) << std::endl;
            }
        
        // ==================== УНИВЕРСАЛЬНАЯ КОМАНДА ВЫВОДА ====================
        } else if (cmd == "PRINT") {
            std::string name;
            ss >> name;
            Entry* e = find_entry(name);
            if (!e) return;
            if (e->type == "ARRAY") {
                std::cout << array_read((Array*)e->ptr) << std::endl;
            } else if (e->type == "FLIST") {
                std::cout << flist_read((Forward_List*)e->ptr) << std::endl;
            } else if (e->type == "DLIST") {
                std::cout << dlist_read((Doubly_List*)e->ptr) << std::endl;
            } else if (e->type == "STACK") {
                std::cout << stack_read((Stack*)e->ptr) << std::endl;
            } else if (e->type == "QUEUE") {
                std::cout << queue_read((Queue*)e->ptr) << std::endl;
            } else if (e->type == "TREE") {
                std::cout << tree_read((Tree*)e->ptr) << std::endl;
            }
        
        // ==================== НЕИЗВЕСТНАЯ КОМАНДА ====================
        } else {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}