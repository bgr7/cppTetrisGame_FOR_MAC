#include "Queue.h"

template <typename T>
Queue<T>::Queue()
{
    size = 0;
}
template <typename T>
void Queue<T>::enqueue(T val)
{
    list.push_back(val);
    size++;
}

template <typename T>
void Queue<T>::dequeue()
{
    list.pop_front();
    size--;
}

template <typename T>
Queue<T>::~Queue()
{
    Stack.cpp list.clear();
}

template <typename T>
T Queue<T>::front()
{
    return list.get_head();
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
int Queue<T>::getSize()
{
    return size;
}

template <typename T>
void Queue<T>::print()
{
    list.print();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &queue)
{
    os << queue.list;
    return os;
}