#pragma once

#include <stdexcept>
#include <cstdlib>
#include <algorithm>

#include <log/Log.h>

namespace GIS {

template<typename T>
class VectorIterator;

template<typename T>
class VectorConstIterator;

template<typename T>
class Vector {
public:
    typedef VectorIterator<T> iterator;
    typedef VectorConstIterator<T> const_iterator;
    typedef long int size_type;

    Vector() : m_size(0) {
        m_capacity = 8;
        m_values = static_cast<T*>(::operator new (sizeof(T[m_capacity])));
    }
    Vector(size_type size) {
        m_values = static_cast<T*>(::operator new (sizeof(T[size])));
        for (size_type i = 0; i < size; i++)
            new (m_values + i) T();
        m_size = size;
        m_capacity = size;
    }
    Vector(size_type size, const T &value) {
        m_values = static_cast<T*>(::operator new (sizeof(T[size])));
        for (size_type i = 0; i < size; i++)
            new (m_values + i) T(value);
        m_size = size;
        m_capacity = size;
    }

    Vector(const Vector &v) {
        m_values = static_cast<T*>(::operator new (sizeof(T(v.m_capacity))));
        copy(m_values, v.m_values, v.size());
        m_size = v.size();
        m_capacity = v.capacity();
    }
    Vector(Vector &&v) {
        m_values = v.m_values;
        m_size = v.m_size;
        m_capacity = v.m_capacity;

        v.m_capacity = 8;
        v.m_values = static_cast<T*>(::operator new (sizeof(T(m_capacity))));

    }

    ~Vector() {
        clear();
    }

    Vector& operator=(const Vector &v) {
        if (this == &v)
            return *this;
        reserve(v.size());
        copy(m_values, v.m_values, v.size());
        return *this;
    }
    Vector& operator=(Vector &&v) {
        if (this == &v)
            return *this;
        reserve(v.size());
        move(m_values, v.m_values, v.size());
        return *this;
    }

    iterator begin() {
        return iterator(m_values);
    }
    iterator end() {
        return iterator(m_values + m_size);
    }

    void resize(size_type size) {
        if (m_size == size)
            return;
        if (m_capacity < size) {
            expand(size);
        } else {
            for (size_type i = size; i < m_size; i++) {
                m_values[i].~T();
            }
        }
        m_size = size;

    }
    void resize(size_type size, const T &value) {
        if (m_size == size)
            return;
        if (m_capacity < size) {
            expand(size, value);
        } else {
            for (size_type i = size; i < m_size; i++) {
                m_values[i].~T();
            }
            m_size = size;
        }
    }

    void reserve(size_type capacity) {
        if (capacity <= m_capacity)
            return;
        T *newContainer = static_cast<T*> (::operator new(sizeof(T[capacity])));
        move(newContainer, m_values, m_size);
        clear();
        m_values = newContainer;
        m_capacity = capacity;
    }

    void push_back(const T &value) {
        if (m_size == m_capacity) {
            reserve(2 * m_capacity);
        }
        new (m_values + m_size) T(value);
        m_size++;
    }
    void push_back(T &&value) {
        if (m_size == m_capacity) {
            reserve(2 * m_capacity);
        }
        new (m_values + m_size) T(std::move(value));
        m_size++;
    }

    void erase(iterator it) {
        erase(it.m_ptr, it.m_ptr + 1);
    }

    void erase(iterator from, iterator to) {
        erase(from.m_ptr, to.m_ptr);
    }

    T& front() noexcept {
        return m_values[0];
    }

    const T& front() const noexcept {
        return m_values[0];
    }

    T& back() noexcept {
        return m_values[m_size - 1];
    }

    const T& back() const noexcept {
        return m_values[m_size - 1];
	}

    T& operator[](size_type n) noexcept {
        return m_values[n];
    }

    const T& operator[](size_type n) const noexcept {
        return m_values[n];
    }

    T& at(size_type n) {
        range_check(n);
        return m_values[n];
    }

    const T& at(size_type n) const {
        range_check(n);
        return m_values[n];
    }

    T* data() noexcept {
        return m_values;
    }

    size_type size() const noexcept {
        return m_size;
    }

    size_type capacity() const noexcept {
        return m_capacity;
    }

    bool empty() {
        return begin() == end();
    }
    void clear() {
        for (size_type i = 0; i < m_size; i++) {
            m_values[i].~T();
        }
        ::operator delete(m_values);
        m_values = nullptr;
    }

private:
    void erase(T* from, T* to) {
        unsigned to_erase = to- from;
        auto ptr = from;
        for (; ptr < m_values + m_size - to_erase; ptr++) {
            *ptr = std::move(*(ptr + 1));
        }
        for (; ptr < m_values + m_size; ptr++) {
            ptr->~T();
        }
        m_size -= to_erase;
    }

    void copy(T* to, const T* from, size_type toCopy) {
        for (size_type i = 0; i < toCopy; i++) {
            new(to + i) T(from[i]);
        }
    }

    void move(T* to, T* from, size_type toMove) {
        for (size_type i = 0; i < toMove; i++) {
            new(to + i) T(std::move(from[i]));
        }

    }
    template <typename... Args>
    void expand(size_type size, Args... args) {
        T *newValues = static_cast<T*> (::operator new(sizeof(T[size])));
        size_type toMove = std::min(m_size, size);

        move(newValues, m_values, toMove);
        for (size_type i = toMove; i < size; i++)
            new (newValues + i) T(args...);
        clear();
        m_values = newValues;
        m_capacity = size;
        m_size = toMove;
    }

    void range_check(size_type n) const {
        if (n > m_size)
                throw std::out_of_range("Accessing element " + std::to_string(n) + " in Vector of size"
                                        + std::to_string(m_size));
    }
    T* m_values;
    size_type m_size;
    size_type m_capacity;
    friend class VectorIterator<T>;
};

template<typename T>
class VectorIterator {
public:
    typedef VectorIterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef long int difference_type;
    VectorIterator() : m_ptr(nullptr) {}
    reference operator*() const {
        return *m_ptr;
    }
    pointer operator->() const {
        return m_ptr;
    }
    self_type& operator++() {
        m_ptr++;
        return *this;
    }
    self_type operator++(int) {
        VectorIterator tmp = *this;
        m_ptr++;
        return tmp;
    }

    self_type& operator--() {
        m_ptr--;
        return *this;
    }

    self_type operator--(int) {
        VectorIterator tmp = *this;
        m_ptr--;
        return tmp;
    }

    self_type operator+(int off) {
        return VectorIterator(m_ptr + off);
    }

    self_type operator-(int off) {
        return VectorIterator(m_ptr - off);
    }

    difference_type operator-(const self_type& other) {
        return m_ptr - other.m_ptr;
    }

    bool operator<(const self_type &other) const {
        return m_ptr < other.m_ptr;
    }

    bool operator==(const self_type &other) const {
        return other.m_ptr == m_ptr;
    }
    bool operator!=(const self_type &other) const {
        return other.m_ptr != m_ptr;
    }

private:
    VectorIterator(T *ptr) : m_ptr(ptr) {}
    T *m_ptr;
    friend class Vector<T>;
};

/*template<typename T>
class VectorConstIterator {
public:
    const T& operator*() const {
        return *m_ptr;
    }
    const T* operator->() const {
        return m_ptr;
    }
    VectorConstIterator& operator++(){
        VectorConstIterator tmp = *this;
        m_ptr++;
        return tmp;
    }
    VectorConstIterator& operator++(int){
        m_ptr++;
        return *this;
    }
    bool operator==(const VectorConstIterator &other) const {
        return other.m_ptr == m_ptr;
    }
    bool operator!=(const VectorConstIterator &other) const {
        return other.m_ptr != m_ptr;
    }
private:
    VectorConstIterator(T *ptr) : m_ptr(ptr) {}

    T *m_ptr;
    friend class Vector<T>;

};
*/
}
