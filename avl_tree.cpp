#include "avl_tree.h"
#include <stdexcept>

// Вспомогательные функции для AVL-дерева

// Получение высоты узла
int get_height(TreeNode* node) {
    return node ? node->height : 0;
}

// Вычисление баланс-фактора
int get_balance(TreeNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

// Обновление высоты узла (без std::max)
void update_height(TreeNode* node) {
    if (node) {
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);
        node->height = 1 + (left_height > right_height ? left_height : right_height);
    }
}

// Правый поворот
TreeNode* rotate_right(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // Выполняем поворот
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    update_height(y);
    update_height(x);

    return x;
}

// Левый поворот
TreeNode* rotate_left(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // Выполняем поворот
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    update_height(x);
    update_height(y);

    return y;
}

// Балансировка узла
TreeNode* balance_node(TreeNode* node) {
    if (!node) return node;

    // Обновляем высоту текущего узла
    update_height(node);

    // Получаем баланс-фактор
    int balance = get_balance(node);

    // Левый левый случай
    if (balance > 1 && get_balance(node->left) >= 0) {
        return rotate_right(node);
    }

    // Левый правый случай
    if (balance > 1 && get_balance(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // Правый правый случай
    if (balance < -1 && get_balance(node->right) <= 0) {
        return rotate_left(node);
    }

    // Правый левый случай
    if (balance < -1 && get_balance(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    // Балансировка не требуется
    return node;
}

// Рекурсивная вставка для AVL-дерева
TreeNode* insert_node(TreeNode* node, const std::string& value) {
    // Обычная вставка в BST
    if (!node) {
        TreeNode* newNode = new TreeNode{value, nullptr, nullptr, 1};
        return newNode;
    }

    if (value < node->data) {
        node->left = insert_node(node->left, value);
    } else if (value > node->data) {
        node->right = insert_node(node->right, value);
    } else {
        // Дубликаты не разрешены
        return node;
    }

    // Балансировка дерева
    return balance_node(node);
}

// Создание пустого дерева
Tree* create_tree(const std::string& name) {
    Tree* tree = new Tree;
    tree->name = name;
    tree->root = nullptr;
    return tree;
}

// Вставка в AVL-дерево - O(log n)
void tree_insert(Tree* tree, const std::string& value) {
    tree->root = insert_node(tree->root, value);
}

// Поиск в AVL-дереве - O(log n)
bool tree_find(const Tree* tree, const std::string& value) {
    TreeNode* current = tree->root;
    
    while (current) {
        if (value == current->data) {
            return true;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return false;
}

// Рекурсивное вычисление высоты для обхода в ширину
int tree_height(TreeNode* node) {
    if (!node) return 0;
    int left = tree_height(node->left);
    int right = tree_height(node->right);
    return (left > right ? left : right) + 1;
}

// Печать уровня для обхода в ширину
void print_level(TreeNode* node, int level, std::string& result) {
    if (!node) return;
    if (level == 1) {
        if (!result.empty()) result += " ";
        result += node->data;
    } else {
        print_level(node->left, level - 1, result);
        print_level(node->right, level - 1, result);
    }
}

// Обход в ширину для чтения структуры дерева - O(n)
std::string tree_read(const Tree* tree) {
    if (!tree->root) return "";
    
    std::string result;
    int h = tree_height(tree->root);
    for (int i = 1; i <= h; i++) {
        print_level(tree->root, i, result);
    }
    
    return result;
}

// In-order обход для отсортированного вывода - O(n)
void inorder_traversal(TreeNode* node, std::string& result) {
    if (!node) return;
    inorder_traversal(node->left, result);
    if (!result.empty()) result += " ";
    result += node->data;
    inorder_traversal(node->right, result);
}

std::string tree_read_sorted(const Tree* tree) {
    std::string result;
    inorder_traversal(tree->root, result);
    return result;
}

// Проверка полноты дерева - O(n)
bool tree_is_full(const TreeNode* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (root->left && root->right) 
        return tree_is_full(root->left) && tree_is_full(root->right);
    return false;
}

// Освобождение памяти
void destroy_tree(TreeNode* root) {
    if (root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        delete root;
    }
}

void destroy_tree_struct(Tree* tree) {
    destroy_tree(tree->root);
    delete tree;
}