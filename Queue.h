#pragma once
#include "LinkedList.h"
#include "Node.h"

template <typename T>
class Queue
{
private:
    LinkedList<T> list;
    int size;

public:
    Queue();
    ~Queue();
    void enqueue(T val);
    void dequeue();
    T front();
    bool isEmpty();
    int getSize();
    void print();
    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &queue);
};
