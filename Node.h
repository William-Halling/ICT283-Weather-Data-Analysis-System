#ifndef NODE_H
#define NODE_H

#include <memory>
#include <utility>

template<typename T>
struct Node 
{
    T data;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    explicit Node(T value) 
        : data(std::move(value)), left(nullptr), right(nullptr) {}
        
    ~Node() = default;
};

#endif // NODE_H
