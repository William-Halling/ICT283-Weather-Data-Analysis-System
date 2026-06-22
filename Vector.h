#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <vector>
#include <utility>

template <class T>
class Vector 
{
public:
    Vector() = default;
    explicit Vector(size_t numItems) : m_Records(numItems) {}
    
    Vector(const Vector& other) = default;
    Vector(Vector&& other) noexcept = default;
    ~Vector() = default;

    Vector& operator=(const Vector& other) = default;
    Vector& operator=(Vector&& other) noexcept = default;

    [[nodiscard]] T& operator[](size_t recordNumber) { return m_Records[recordNumber]; }
    [[nodiscard]] const T& operator[](size_t recordNumber) const { return m_Records[recordNumber]; }

    [[nodiscard]] size_t size() const noexcept { return m_Records.size(); }
    [[nodiscard]] bool empty() const noexcept { return m_Records.empty(); }
    
    void push_back(const T& newRecord) { m_Records.push_back(newRecord); }
    void push_back(T&& newRecord) { m_Records.push_back(std::move(newRecord)); }

    void clear() noexcept { m_Records.clear(); }

    [[nodiscard]] std::vector<T>& data() noexcept { return m_Records; }
    [[nodiscard]] const std::vector<T>& data() const noexcept { return m_Records; }

private:
    std::vector<T> m_Records;
};

#endif // VECTOR_H
