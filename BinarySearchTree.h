#ifndef BST_H
#define BST_H

#include "Node.h"
#include <functional>

template<typename T>
class BinarySearchTree {
private:
    std::unique_ptr<Node<T>> root;


    // Recursive helper for insertion
    void insert(std::unique_ptr<Node<T>>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node<T>>(value);
            return;
        }
        if (value < node->data) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }


    // In-order traversal using modern std::function
    void inOrder(const std::unique_ptr<Node<T>>& node, const std::function<void(const T&)>& func) const {
        if (!node) return;
        inOrder(node->left, func);
        func(node->data);
        inOrder(node->right, func);
    }


public:
    BinarySearchTree() : root(nullptr) {}

    // Disable copying to prevent tree duplication; enforce moving if needed
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;


    void insert(const T& value) {
        insert(root, value);
    }


    void traverseInOrder(const std::function<void(const T&)>& func) const {
        inOrder(root, func);
    }


    bool isEmpty() const noexcept { return root == nullptr; }
};

#endif
