#include "Stack.h"

template <typename T>
Stack<T>::Stack()
{
    size = 0;
}
template <typename T>
void Stack<T>::push(T val)
{
    list.push_back(val);
    size++;
}
template <typename T>
void Stack<T>::pop()
{
    list.pop_back();
    size--;
}
template <typename T>
Stack<T>::~Stack()
{
    list.clear();
}

template <typename T>
T Stack<T>::top()
{
    return list.get_head();
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
int Stack<T>::getSize()
{
    return size;
}

template <typename T>
void Stack<T>::print()
{
    list.print();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack)
{
    os << stack.list;
    return os;
}
