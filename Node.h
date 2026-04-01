#pragma once
#include <memory>
#include <utility>

template<typename T>
struct Node 
{
    T data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    // explicit prevents accidental implicit type conversions
    explicit Node(T storedData) : data(std::move(storedData)) {}
    
    // Default destructor is safe; unique_ptr automatically cleans up children
    ~Node() = default; 
};
