#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

#include <string>

struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;
    int height;  // Высота узла для балансировки AVL
};

struct Tree {
    std::string name;
    TreeNode* root;
};

// Функции для работы с AVL-деревом
Tree* create_tree(const std::string& name);
void tree_insert(Tree* tree, const std::string& value);
bool tree_find(const Tree* tree, const std::string& value);
bool tree_is_full(const TreeNode* root);
std::string tree_read(const Tree* tree);           // Обход в ширину
std::string tree_read_sorted(const Tree* tree);    // In-order (отсортированный)
void destroy_tree(TreeNode* root);
void destroy_tree_struct(Tree* tree);

#endif