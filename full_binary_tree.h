#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

#include <string>

struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;
};

struct Tree {
    std::string name;
    TreeNode* root;
};

// Основные операции
Tree* create_tree(const std::string& name);
void tree_insert(Tree* tree, const std::string& value);
bool tree_find(const Tree* tree, const std::string& value);
bool tree_is_full(const Tree* tree);  // Изменено: принимает Tree*, а не TreeNode*
std::string tree_read(const Tree* tree);

// Уничтожение дерева
void destroy_tree(Tree* tree);

#endif