#pragma once

template <class T>
class vector
{
public:
    typedef T *iterator;

    vector();
    vector(int size);
    vector(int size, const T &initial);
    vector(const vector<T> &v);
    ~vector();
    int size() const;
    bool empty() const;
    int capacity() const;
    void push_back(const T &value);
    void pop_back();
    void reserve(int capacity);
    void resize(int size);
    void clear();
    iterator begin();
    iterator end();
    T &front();
    T &back();
    T &operator[](int index);
    vector<T> &operator=(const vector<T> &);

private:
    int my_size;
    int my_capacity;
    T *buffer;
};
