#ifndef NODE_H
#define NODE_H

#include <memory>

template<typename T>
struct Node 
{
    T data;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    explicit Node(const T& value) : data(value) {}
    explicit Node(T&& value) : data(std::move(value)) {}
        
    ~Node() = default;
};

#endif // NODE_H
