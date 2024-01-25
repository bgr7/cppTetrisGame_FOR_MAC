#pragma once
#include "LinkedList.h"
#include "Node.h"

template <typename T>
class Stack
{
private:
    LinkedList<T> list;
    int size;

public:
    Stack();
    ~Stack();
    void push(T val);
    void pop();
    T top();
    bool isEmpty();
    int getSize();
    void print();
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &stack);
};