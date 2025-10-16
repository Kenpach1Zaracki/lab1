#ifndef STORAGE_H
#define STORAGE_H

#include <string>

struct Entry {
    std::string type;
    void* ptr;
    std::string name;
};

extern Entry entries[100];
extern int entryCount;

Entry* find_entry(const std::string& name);
void save_to_file(const std::string& filename);
void load_from_file(const std::string& filename);

#endif
