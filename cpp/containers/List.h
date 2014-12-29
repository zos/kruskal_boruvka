#pragma once

#include <algorithm>

namespace GIS {

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template<typename T>
class List {
public:

    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;
    typedef List<T> Node;

    typedef long int size_type;

    List() : m_value(nullptr), m_next(this), m_prev(this), m_size(0) {

    }

    List(size_type size) : m_value(nullptr), m_next(this), m_prev(this), m_size(0) {
        for (size_type i = 0; i < size; i++)
            insert(end(), T());
    }
    List(size_type size, const T &value) : m_value(nullptr), m_next(this), m_prev(this), m_size(0) {
        for (size_type i = 0; i < size; i++)
            insert(end(), value);
    }
    List(const List &other) : m_value(nullptr), m_next(this), m_prev(this), m_size(0) {
        for(auto &node : other) {
            insert(end(), node);
        }
    }
    List(List &&other)
        : m_value(other.m_value),
          m_next(other.m_next),
          m_prev(other.m_prev),
          m_size(other.m_size)
    {
        other.m_value = nullptr;
        other.m_prev = nullptr;
        other.m_next = nullptr;
        other.m_size = 0;
    }

    ~List() {
        while(m_size)
            erase(begin());
    }

    List& operator=(const List &other) {
        if (this == &other)
            return *this;
        //clear
        clear();
        for(auto &node : other) {
            insert(end(), node);
        }
        return *this;

    }
    List& operator=(List &&other) {
        if (this == &other)
            return *this;
        clear();
        m_value = other.m_value;
        m_next = other.m_next;
        m_prev = other.m_prev;
        m_size = other.m_size;

        other.m_value = nullptr;
        other.m_prev = nullptr;
        other.m_next = nullptr;
        other.m_size = 0;

        return *this;
    }

    iterator insert(iterator pos, const T &value) {
        Node *newNode = new Node(value);
        newNode->m_prev = pos.m_ptr->m_prev;
        newNode->m_next = pos.m_ptr;

        pos.m_ptr->m_prev->m_next = newNode;
        pos.m_ptr->m_prev = newNode;

        m_size++;

        return iterator(newNode);

    }

    iterator insert(iterator pos, T &&value) {
        Node *newNode = new Node(std::move(value));
        newNode->m_prev = pos.m_ptr->m_prev;
        newNode->m_next = pos.m_ptr;

        pos.m_ptr->m_prev->m_next = newNode;
        pos.m_ptr->m_prev = newNode;

        m_size++;

        return iterator(newNode);
    }
    //iterator insert(const_iterator pos, const T &value);
    //iterator insert(const_iterator pos, T &&value);

    void push_back(const T& value) {
        insert(end(), value);
    }
    void push_back(T&& value) {
        insert(end(), std::move(value));
    }

    void push_front(const T& value) {
        insert(begin(), value);
    }
    void push_front(T &&value) {
        insert(begin(), std::move(value));
    }

    iterator erase(iterator pos) {
        pos.m_ptr->m_next->m_prev = pos.m_ptr->m_prev;
        pos.m_ptr->m_prev->m_next = pos.m_ptr->m_next;

        auto it = iterator(pos.m_ptr->m_next);

        delete pos.m_ptr;
        m_size--;

        return it;
    }

    void pop_back() {
        erase(iterator(m_prev));
    }

    void pop_front() {
        erase(iterator(m_next));
    }

    T& front() {
        return *(m_next->m_value);
    }
    T& back() {
        return *(m_prev->m_value);
    }

    iterator begin() {
        return iterator(m_next);
    }
    iterator end() {
        return iterator(this);
    }

    const_iterator begin() const {
        return const_iterator(m_next);
    }

    const_iterator end() const {
        return const_iterator(this);
    }

    size_type size() const {
        return m_size;
    }

    void clear() {
        while(m_size)
            erase(begin());
    }

    bool empty() {
        return m_next == m_prev;
    }

private:
    List(const T &value) : m_next(nullptr), m_prev(nullptr), m_size(0) {
        m_value = new T(value);
    }
    List(T &&value) : m_next(nullptr), m_prev(nullptr), m_size(0) {
        m_value = new T(std::move(value));
    }
    T *m_value;
    Node *m_next;
    Node *m_prev;
    size_type m_size;

    friend class ListIterator<T>;
    friend class ListConstIterator<T>;
};


template <typename T>
class ListIterator {
public:
    typedef ListIterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef long int difference_type;
    typedef List<T> Node;

    ListIterator(const ListIterator &it) : m_ptr(it.m_ptr) {}
    ListIterator& operator=(const ListIterator &other) {
        m_ptr = other.m_ptr;
        return *this;
    }
    ListIterator operator++() {
        ListIterator it = *this;
        m_ptr = m_ptr->m_next;
        return it;
    }
    ListIterator& operator++(int junk) {
        (void) junk;
        m_ptr = m_ptr->m_next;
        return *this;
    }
    T& operator*() { return *(m_ptr->m_value); }
    T* operator->() { return m_ptr->m_value; }

    bool operator==(const ListIterator &right) {
        return m_ptr == right.m_ptr;
    }
    bool operator!=(const ListIterator &right) {
        return !(*this == right);
    }

private:
    Node* m_ptr;
    ListIterator(Node *ptr) : m_ptr(ptr) {}

    friend class List<T>;
};

template <typename T>
class ListConstIterator {
public:
    typedef ListConstIterator self_type;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef long int difference_type;
    typedef List<T> Node;

    ListConstIterator(const ListConstIterator &it) : m_ptr(it.m_ptr) {}
    self_type& operator=(const ListConstIterator &other) {
        m_ptr = other.m_ptr;
        return *this;
    }
    self_type operator++() {
        ListConstIterator it = *this;
        m_ptr = m_ptr->m_next;
        return it;
    }
    self_type& operator++(int junk) {
        (void) junk;
        m_ptr = m_ptr->m_next;
        return *this;
    }
    reference operator*() { return *(m_ptr->m_value); }
    pointer operator->() { return m_ptr->m_value; }
    bool operator==(const self_type &right) {
        return m_ptr == right.m_ptr;
    }
    bool operator!=(const self_type &right) {
        return !(*this == right);
    }

private:
    const Node* m_ptr;
    ListConstIterator(const Node *ptr) : m_ptr(ptr) {}

    friend class List<T>;
};

}

