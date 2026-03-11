#ifndef BST_H
#define BST_H

#include "Node.h"

template<typename T>
class BinarySearchTree
{
private:

    Node<T>* root;

    void insert(Node<T>*& node, const T& value)
    {
        if (!node)
        {
            node = new Node<T>(value);

            return;
        }

        if (value < node->data)
            insert(node->left, value);
        else
            insert(node->right, value);
    }


    void inOrder(Node<T>* node, void (*func)(T&, void*), void* context)
    {
        if (!node) 
            
            return;

        inOrder(node->left, func, context);
        func(node->data, context);
        inOrder(node->right, func, context);
    }


    void preOrder(Node<T>* node, void (*func)(T&, void*), void* context)
    {
        if (!node)
            
            return;

        func(node->data, context);
        preOrder(node->left, func, context);
        preOrder(node->right, func, context);
    }


    void postOrder(Node<T>* node, void (*func)(T&, void*), void* context)
    {
        if (!node) 
            
            return;

        postOrder(node->left, func, context);
        postOrder(node->right, func, context);
        func(node->data, context);
    }


public:

    BinarySearchTree() : root(nullptr) {}

    void insert(const T& value)
    {
        insert(root, value);
    }


    void traverseInOrder(void (*func)(T&, void*), void* context)
    {
        inOrder(root, func, context);
    }


    void traversePreOrder(void (*func)(T&, void*), void* context)
    {
        preOrder(root, func, context);
    }


    void traversePostOrder(void (*func)(T&, void*), void* context)
    {
        postOrder(root, func, context);
    }
};

#endif