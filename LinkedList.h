#pragma once
#include "Node.h"
#include <iostream>
#include <exception>
template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    Node<T> *getNode(const int index) const;

public:
    LinkedList();
    ~LinkedList();
    void isEmpty();
    int get_head() const;
    void push_back(T val);
    void push_front(T val);
    void pop_back();
    void pop_front();
    void insert(T val, int index);
    void remove(int index);
    void clear();
    int get_size();
    void print();
    void reverse();
    void sort();
    void merge(LinkedList<T> &list);
    T &operator[](int index);
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list);
};
