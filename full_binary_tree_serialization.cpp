#include "full_binary_tree_serialization.h"
#include <queue>
#include <vector>

void serialize_node_binary(std::ofstream& ofs, TreeNode* node) {
    if (!node) {
        bool is_null = true;
        ofs.write(reinterpret_cast<char*>(&is_null), sizeof(bool));
        return;
    }
    
    bool is_null = false;
    ofs.write(reinterpret_cast<char*>(&is_null), sizeof(bool));
    
    size_t len = node->data.length();
    ofs.write(reinterpret_cast<char*>(&len), sizeof(size_t));
    ofs.write(node->data.c_str(), len);
    
    serialize_node_binary(ofs, node->left);
    serialize_node_binary(ofs, node->right);
}

void tree_serialize_binary(const Tree* tree, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    
    size_t name_len = tree->name.length();
    ofs.write(reinterpret_cast<const char*>(&name_len), sizeof(size_t));
    ofs.write(tree->name.c_str(), name_len);
    
    serialize_node_binary(ofs, tree->root);
    ofs.close();
}

TreeNode* deserialize_node_binary(std::ifstream& ifs) {
    bool is_null;
    ifs.read(reinterpret_cast<char*>(&is_null), sizeof(bool));
    
    if (is_null) return nullptr;
    
    size_t len;
    ifs.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    
    std::string data(len, '\0');
    ifs.read(&data[0], len);
    
    TreeNode* node = new TreeNode{data, nullptr, nullptr};
    node->left = deserialize_node_binary(ifs);
    node->right = deserialize_node_binary(ifs);
    
    return node;
}

Tree* tree_deserialize_binary(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    
    size_t name_len;
    ifs.read(reinterpret_cast<char*>(&name_len), sizeof(size_t));
    
    std::string name(name_len, '\0');
    ifs.read(&name[0], name_len);
    
    Tree* tree = create_tree(name);
    tree->root = deserialize_node_binary(ifs);
    
    ifs.close();
    return tree;
}

void tree_serialize_text(const Tree* tree, const std::string& filename) {
    std::ofstream ofs(filename);
    ofs << tree->name << "\n";
    
    if (!tree->root) {
        ofs.close();
        return;
    }
    
    std::queue<TreeNode*> q;
    q.push(tree->root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node) {
            ofs << node->data << " ";
            q.push(node->left);
            q.push(node->right);
        } else {
            ofs << "null ";
        }
    }
    
    ofs.close();
}

Tree* tree_deserialize_text(const std::string& filename) {
    std::ifstream ifs(filename);
    std::string name;
    std::getline(ifs, name);
    
    Tree* tree = create_tree(name);
    
    std::string line;
    std::getline(ifs, line);
    
    if (line.empty()) {
        ifs.close();
        return tree;
    }
    
    std::istringstream iss(line);
    std::vector<std::string> values;
    std::string value;
    
    while (iss >> value) {
        values.push_back(value);
    }
    
    if (values.empty() || values[0] == "null") {
        ifs.close();
        return tree;
    }
    
    tree->root = new TreeNode{values[0], nullptr, nullptr};
    std::queue<TreeNode*> q;
    q.push(tree->root);
    
    size_t i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (i < values.size() && values[i] != "null") {
            node->left = new TreeNode{values[i], nullptr, nullptr};
            q.push(node->left);
        }
        i++;
        
        if (i < values.size() && values[i] != "null") {
            node->right = new TreeNode{values[i], nullptr, nullptr};
            q.push(node->right);
        }
        i++;
    }
    
    ifs.close();
    return tree;
}
