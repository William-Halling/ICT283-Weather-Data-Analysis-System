#ifndef NODE_H
#define NODE_H

#include <memory>
#include <utility>

/**
 * @struct Node
 * @brief Template node for a Binary Search Tree using RAII for memory management.
 */
template<typename T>
struct Node {
    T data;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    // Explicit constructor prevents accidental type conversions
    explicit Node(T value) 
        : data(std::move(value)), left(nullptr), right(nullptr) {}

    // No manual destructor needed; unique_ptr handles cleanup
    ~Node() = default;
};

#endif
