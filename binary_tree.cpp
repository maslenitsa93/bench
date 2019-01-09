#include "binary_tree.h"

binary_tree::binary_tree() {
    root = nullptr;
}

binary_tree::~binary_tree() {
    clear();
}

void binary_tree::free(node* leaf) {
    if (leaf != nullptr) {
        free(leaf->left);
        free(leaf->right);
        delete leaf;
    }
}

void binary_tree::clear() {
    free(root);
}

node* binary_tree::search(int key, node* leaf) {
    if (leaf != nullptr) {
        if (key == leaf->key) {
            return leaf;
        }

        if(key < leaf->key) {
            return search(key, leaf->left);
        }

        return search(key, leaf->right);
    }
    return nullptr;
}

node* binary_tree::search(int key) {
    return search(key, root);
}

void binary_tree::insert(int key, node* leaf) {
    if (key < leaf->key) {
        if (leaf->left != nullptr) {
            insert(key, leaf->left);
        } else {
            leaf->left = new node;
            leaf->left->key = key;
        }
        return;
    }

    if(leaf->right != nullptr) {
        insert(key, leaf->right);
    } else {
        leaf->right = new node;
        leaf->right->key = key;
    }
}

void binary_tree::insert(int key) {
    if (root != nullptr) {
        insert(key, root);
    } else {
        root = new node;
        root->key = key;
    }
}

node* min_node(node* leaf) {
    node* current = leaf;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

node* binary_tree::remove(int key, node* root) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = remove(key, root->left);
    } 
    else if (key > root->key) {
        root->right = remove(key, root->right);
    }
    else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return root;
        }
        else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return root;
        }

        node* temp = min_node(root->right);
        root->key = temp->key;
        root->right = remove(temp->key, root->right);
    }

    return root;
}

void binary_tree::remove(int key) {
    root = remove(key, root);
}



















