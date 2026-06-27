#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"
#include <functional>
#include <utility>

namespace container {

template <typename T>
class BinarySearchTree 
{
public:
    BinarySearchTree() noexcept : root_(nullptr) {}
    ~BinarySearchTree() = default;

    // Rule of 5: Disable copying
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept : root_(std::move(other.root_)) {}

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept 
    {
        if (this != &other) 
        {
            root_ = std::move(other.root_);
        }
        return *this;
    }


    void insert(const T& value) 
    {
        insertNode(root_, value);
    }


    void insert(T&& value)
    {
        insertNode(root_, std::move(value));
    }

    template <typename F, typename... Args>
    void inOrderTraverse(F&& func, Args&&... args) const
    {
        inOrder(root_.get(), std::forward<F>(func), std::forward<Args>(args)...);
    }

    template <typename F, typename... Args>
    void preOrderTraverse(F&& func, Args&&... args) const
    {
        preOrder(root_.get(), std::forward<F>(func), std::forward<Args>(args)...);
    }

    template <typename F, typename... Args>
    void postOrderTraverse(F&& func, Args&&... args) const 
    {
        postOrder(root_.get(), std::forward<F>(func), std::forward<Args>(args)...);
    }

private:
    void insertNode(std::unique_ptr<Node<T>>& node, const T& value) 
    {
        if (!node) 
        {
            node = std::make_unique<Node<T>>(value);
            
            return;
        }
        
        if (value < node->data) 
        {
            insertNode(node->left, value);
        } 
            
        else 
        {
            insertNode(node->right, value);
        }
    }

    void insertNode(std::unique_ptr<Node<T>>& node, T&& value) 
    {
        if (!node) 
        {
            node = std::make_unique<Node<T>>(std::move(value));
            
            return;
        }
        
        if (value < node->data)
        {
            insertNode(node->left, std::move(value));
        } 
        else 
        {
            insertNode(node->right, std::move(value));
        }
    }

    template <typename F, typename... Args>
    void inOrder(Node<T>* node, F&& func, Args&&... args) const 
    {
        if (!node) 
        {
            return;
        }
        inOrder(node->left.get(), func, args...);
        func(node->data, args...);
        inOrder(node->right.get(), func, args...);
    }

    template <typename F, typename... Args>
    void preOrder(Node<T>* node, F&& func, Args&&... args) const 
    {
        if (!node) 
        {
            return;
        }
        func(node->data, std::forward<Args>(args)...);
        preOrder(node->left.get(), std::forward<F>(func), std::forward<Args>(args)...);
        preOrder(node->right.get(), std::forward<F>(func), std::forward<Args>(args)...);
    }

    template <typename F, typename... Args>
    void postOrder(Node<T>* node, F&& func, Args&&... args) const 
    {
        if (!node) 
        {
            return;
        }
        postOrder(node->left.get(), std::forward<F>(func), std::forward<Args>(args)...);
        postOrder(node->right.get(), std::forward<F>(func), std::forward<Args>(args)...);
        func(node->data, std::forward<Args>(args)...);
    }

    std::unique_ptr<Node<T>> root_;
};
}

#endif // BINARYSEARCHTREE_H
