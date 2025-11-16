#ifndef FULL_BINARY_TREE_SERIALIZATION_H
#define FULL_BINARY_TREE_SERIALIZATION_H

#include "full_binary_tree.h"
#include <fstream>
#include <sstream>

// Бинарная сериализация
void tree_serialize_binary(const Tree* tree, const std::string& filename);
Tree* tree_deserialize_binary(const std::string& filename);

// Текстовая сериализация
void tree_serialize_text(const Tree* tree, const std::string& filename);
Tree* tree_deserialize_text(const std::string& filename);

#endif
