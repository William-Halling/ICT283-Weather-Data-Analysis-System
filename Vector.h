#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <vector>
#include <utility>

template <class T>
class Vector 
{
    public:
    using value_type = T;
        using size_type = size_t;
        using reference = T&;
        using const_reference = const T&;
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;
    
        Vector() = default;
        explicit Vector(size_t numItems) : m_Records(numItems) {}
        explicit Vector(size_t numItems, const T& value) : m_Records(numItems, value) {}
    
        Vector(const Vector& other) = default;
        Vector(Vector&& other) noexcept = default;
        ~Vector() = default;
    
        Vector& operator=(const Vector& other) = default;
        Vector& operator=(Vector&& other) noexcept = default;
    
        [[nodiscard]] T& operator[](size_t recordNumber) { return m_Records[recordNumber]; }
        [[nodiscard]] const T& operator[](size_t recordNumber) const { return m_Records[recordNumber]; }
    
    
        [[nodiscard]] T& at(size_t recordNumber) 
        {
            if (recordNumber >= m_Records.size())
            {
                throw std::out_of_range("Vector::at - index out of range");
            }
            return m_Records[recordNumber];
        }
    
        [[nodiscard]] const T& at(size_t recordNumber) const
        {
            if (recordNumber >= m_Records.size())
            {
                throw std::out_of_range("Vector::at - index out of range");
            }
            return m_Records[recordNumber];
        }
    
        [[nodiscard]] size_t size() const noexcept { return m_Records.size(); }
        [[nodiscard]] bool empty() const noexcept { return m_Records.empty(); }
        [[nodiscard]] size_t capacity() const noexcept { return m_Records.capacity(); }
    
        void push_back(const T& newRecord) { m_Records.push_back(newRecord); }
        void push_back(T&& newRecord) { m_Records.push_back(std::move(newRecord)); }
    
    
        template <typename... Args>
        decltype(auto) emplace_back(Args&&... args)
        {
            return m_Records.emplace_back(std::forward<Args>(args)...);
        }
    
        void reserve(size_t newCapacity) { m_Records.reserve(newCapacity); }
        void resize(size_t newSize) { m_Records.resize(newSize); }
        void resize(size_t newSize, const T& value) { m_Records.resize(newSize, value); }
    
        void clear() noexcept { m_Records.clear(); }
        void shrink_to_fit() { m_Records.shrink_to_fit(); }
    
        void erase(size_t index) 
        {
            if (index < m_Records.size())
            {
                m_Records.erase(m_Records.begin() + index);
            }
        }
    
        template <typename Pred>
        void erase_if(Pred&& pred) 
        {
            m_Records.erase(std::remove_if(m_Records.begin(), m_Records.end(), std::forward<Pred>(pred)), m_Records.end());
        }
    
            // Full iterator support
        [[nodiscard]] iterator begin() noexcept { return m_Records.begin(); }
        [[nodiscard]] iterator end() noexcept { return m_Records.end(); }
        [[nodiscard]] const_iterator begin() const noexcept { return m_Records.begin(); }
        [[nodiscard]] const_iterator end() const noexcept { return m_Records.end(); }
        [[nodiscard]] const_iterator cbegin() const noexcept { return m_Records.cbegin(); }
        [[nodiscard]] const_iterator cend() const noexcept { return m_Records.cend(); }
    
            // Raw data access (use sparingly)
        [[nodiscard]] T* data_ptr() noexcept { return m_Records.data(); }
        [[nodiscard]] const T* data_ptr() const noexcept { return m_Records.data(); }
    
        // Read-only view of internal storage (safer than returning non-const ref)
        [[nodiscard]] const std::vector<T>& data() const noexcept { return m_Records; }
    
    private:
        std::vector<T> m_Records;
    };
};

#endif // VECTOR_H
