#include "full_binary_tree.h"
#include <iostream>

TreeNode* add_node(TreeNode* root, const std::string& value) {
    if (!root) return new TreeNode{value, nullptr, nullptr};

    if (value < root->data)
        root->left = add_node(root->left, value);
    else if (value > root->data)
        root->right = add_node(root->right, value);

    return root;
}

bool find_node(TreeNode* root, const std::string& value) {
    if (!root) return false;
    if (root->data == value) return true;
    if (value < root->data) return find_node(root->left, value);
    return find_node(root->right, value);
}

bool is_full_node(TreeNode* root) {
    if (!root) return true;
    if ((root->left == nullptr && root->right != nullptr) ||
        (root->left != nullptr && root->right == nullptr))
        return false;
    return is_full_node(root->left) && is_full_node(root->right);
}

int tree_height(TreeNode* root) {
    if (!root) return 0;
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void print_level(TreeNode* root, int level, std::string& result) {
    if (!root) return;
    if (level == 1) {
        if (!result.empty()) result += " ";
        result += root->data;
    } else {
        print_level(root->left, level - 1, result);
        print_level(root->right, level - 1, result);
    }
}

// Основные функции
Tree* create_tree(const std::string& name) {
    Tree* tree = new Tree;
    tree->name = name;
    tree->root = nullptr;
    return tree;
}

void tree_insert(Tree* tree, const std::string& value) {
    tree->root = add_node(tree->root, value);
}

bool tree_find(const Tree* tree, const std::string& value) {
    return find_node(tree->root, value);
}

bool tree_is_full(const Tree* tree) {
    return is_full_node(tree->root);
}

std::string tree_read(const Tree* tree) {
    if (!tree->root) return "";
    
    std::string result;
    int height = tree_height(tree->root);
    for (int i = 1; i <= height; i++) {
        print_level(tree->root, i, result);
    }
    return result;
}

void destroy_tree_nodes(TreeNode* root) {
    if (root) {
        destroy_tree_nodes(root->left);
        destroy_tree_nodes(root->right);
        delete root;
    }
}

void destroy_tree(Tree* tree) {
    destroy_tree_nodes(tree->root);
    delete tree;
}