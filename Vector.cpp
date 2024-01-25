#include "Vector.h"

template <class T>
vector<T>::vector()
{
    capacities = 0;
    sizes = 0;
    buffer = 0;
}
template <class T>
vector<T>::vector(int size)
{
    capacities = size;
    sizes = size;
    buffer = new T[size];
}
template <class T>
vector<T>::vector(const vector<T> &v)
{
    sizes = v.sizes;
    capacities = v.capacities;
    buffer = new T[sizes];
    for (int i = 0; i < sizes; i++)
        buffer[i] = v.buffer[i];
}
template <class T>
vector<T>::vector(int size, const T &initial)
{
    sizes = size;
    capacities = size;
    buffer = new T[size];
    for (int i = 0; i < size; i++)
        buffer[i] = initial;
    // T();
}

template <class T>
vector<T> &vector<T>::operator=(const vector<T> &v)
{
    delete[] buffer;
    sizes = v.sizes;
    capacities = v.capacities;
    buffer = new T[sizes];
    for (int i = 0; i < sizes; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::begin()
{
    return buffer;
}

template <class T>
typename vector<T>::iterator vector<T>::end()
{
    return buffer + size();
}

template <class T>
T &vector<T>::front()
{
    return buffer[0];
}

template <class T>
T &vector<T>::back()
{
    return buffer[sizes - 1];
}

template <class T>
void vector<T>::push_back(const T &v)
{
    if (sizes >= capacities)
        reserve(capacities + 5);
    buffer[sizes++] = v;
}

template <class T>
void vector<T>::pop_back()
{
    sizes--;
}

template <class T>
void vector<T>::reserve(int capacity)
{
    if (buffer == 0)
    {
        sizes = 0;
        capacities = 0;
    }
    T *Newbuffer = new T[capacity];
    // assert(Newbuffer);
    int l_Size = capacity < sizes ? capacity : sizes;
    // copy (buffer, buffer + l_Size, Newbuffer);

    for (int i = 0; i < l_Size; i++)
        Newbuffer[i] = buffer[i];

    capacities = capacity;
    delete[] buffer;
    buffer = Newbuffer;
}

template <class T>
int vector<T>::size() const //
{
    return sizes;
}

template <class T>
void vector<T>::resize(int size)
{
    reserve(size);
    sizes = size;
}

template <class T>
T &vector<T>::operator[](int index)
{
    return buffer[index];
}

template <class T>
int vector<T>::capacity() const
{
    return capacities;
}

template <class T>
vector<T>::~vector()
{
    delete[] buffer;
}
template <class T>
void vector<T>::clear()
{
    capacities = 0;
    sizes = 0;
    buffer = 0;
}