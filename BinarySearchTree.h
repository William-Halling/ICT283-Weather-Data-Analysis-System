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

    // Disable copying to maintain strict unique ownership rules
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
        
        inOrder(node->left.get(), std::forward<F>(func), std::forward<Args>(args)...);
        func(node->data, std::forward<Args>(args)...);
        inOrder(node->right.get(), std::forward<F>(func), std::forward<Args>(args)...);
    }

    std::unique_ptr<Node<T>> root_;
};

} // namespace container

#endif // BINARYSEARCHTREE_H
