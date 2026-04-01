#pragma once
#include "Node.h"
#include <functional>

template<typename T>
class BinarySearchTree {
private:
    std::unique_ptr<Node<T>> root;

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

    // Modernized traversal using std::function. Const correctness applied.
    void inOrder(const std::unique_ptr<Node<T>>& node, const std::function<void(const T&)>& func) const {
        if (!node) return;
        inOrder(node->left, func);
        func(node->data);
        inOrder(node->right, func);
    }

public:
    BinarySearchTree() = default;

    void insert(const T& value) {
        insert(root, value);
    }

    void traverseInOrder(const std::function<void(const T&)>& func) const {
        inOrder(root, func);
    }
};
