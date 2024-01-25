#pragma once
#include <iostream>

template <typename T>
class BGRVector
{
    T *arr;
    int capacity;
    int current;

public:
    BGRVector() : arr(new T[1]{T()}), capacity(1), current(0) {}

    BGRVector(std::initializer_list<T> initList) : arr(new T[initList.size()]{T()}), capacity(initList.size()), current(0)
    {
        for (const T &item : initList)
        {
            arr[current++] = item;
        }
    }

    BGRVector(const BGRVector &other) : arr(new T[other.capacity]{T()}), capacity(other.capacity), current(other.current)
    {
        for (int i = 0; i < current; ++i)
        {
            arr[i] = other.arr[i];
        }
    }

    ~BGRVector() { delete[] arr; }

    BGRVector &operator=(const BGRVector &other)
    {
        if (this != &other)
        {
            T *new_arr = new T[other.capacity]{T()};
            for (int i = 0; i < other.current; ++i)
            {
                new_arr[i] = other.arr[i];
            }
            delete[] arr;
            arr = new_arr;
            capacity = other.capacity;
            current = other.current;
        }
        return *this;
    }

    T &operator[](int index)
    {
        if (index >= 0 && index < current)
        {
            return arr[index];
        }
        throw std::out_of_range("Index out of bounds");
    }

    bool empty() const { return current == 0; }

    void insert(int index, const T &value)
    {
        if (index < 0 || index > current)
        {
            throw std::out_of_range("Index out of bounds");
        }

        if (current == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < index; ++i)
            {
                temp[i] = arr[i];
            }
            temp[index] = value;
            for (int i = index + 1; i <= current; ++i)
            {
                temp[i] = arr[i - 1];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
            ++current;
        }
        else
        {
            for (int i = current; i > index; --i)
            {
                arr[i] = arr[i - 1];
            }
            arr[index] = value;
            ++current;
        }
    }

    void push_back(const T &data)
    {
        if (current == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
    }

    void erase(int index)
    {
        if (index < 0 || index >= current)
        {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < current - 1; ++i)
        {
            arr[i] = arr[i + 1];
        }
        --current;
    }

    T get(int index)
    {
        if (index < current)
            return arr[index];
        return T();
    }

    void pop() { current--; }

    int size() const { return current; }

    int getcapacity() const { return capacity; }

    void print() const
    {
        if (current == 0)
        {
            std::cout << "Vector is empty" << std::endl;
        }
        else
        {
            for (int i = 0; i < current; i++)
            {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    T *begin() { return arr; }

    const T *begin() const { return arr; }

    T *end() { return arr + current; }
};

template <typename T>
class BGRVector<T *>
{
    T **arr;
    int capacity;
    int current;

public:
    BGRVector() : arr(new T *[1]), capacity(1), current(0) {}

    BGRVector(std::initializer_list<T *> initList) : arr(new T *[initList.size()]
                                                         { nullptr }),
                                                     capacity(initList.size()), current(0)
    {
        for (const T *item : initList)
        {
            arr[current++] = new T(*item);
        }
    }

    BGRVector(const BGRVector &other) : arr(new T *[other.capacity]
                                            { nullptr }),
                                        capacity(other.capacity), current(other.current)
    {
        for (int i = 0; i < current; ++i)
        {
            arr[i] = new T(*other.arr[i]);
        }
    }

    ~BGRVector()
    {
        for (int i = 0; i < current; ++i)
        {
            delete arr[i];
        }
        delete[] arr;
    }

    BGRVector &operator=(const BGRVector &other)
    {
        if (this != &other)
        {
            T **new_arr = new T *[other.capacity]
            { nullptr };
            for (int i = 0; i < other.current; ++i)
            {
                new_arr[i] = new T(*other.arr[i]);
            }
            for (int i = 0; i < current; ++i)
            {
                delete arr[i];
            }
            delete[] arr;
            arr = new_arr;
            capacity = other.capacity;
            current = other.current;
        }
        return *this;
    }

    T *operator[](int index)
    {
        if (index >= 0 && index < current)
        {
            return arr[index];
        }
        throw std::out_of_range("Index out of bounds");
    }

    bool empty() const { return current == 0; }

    void insert(int index, T *value)
    {
        if (index < 0 || index > current)
        {
            throw std::out_of_range("Index out of bounds");
        }

        if (current == capacity)
        {
            T **temp = new T *[2 * capacity]
            { nullptr };
            for (int i = 0; i < index; ++i)
            {
                temp[i] = arr[i];
            }
            temp[index] = new T(*value);
            for (int i = index + 1; i <= current; ++i)
            {
                temp[i] = arr[i - 1];
            }
            for (int i = 0; i < current; ++i)
            {
                delete arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
            ++current;
        }
        else
        {
            for (int i = current; i > index; --i)
            {
                arr[i] = arr[i - 1];
            }
            arr[index] = new T(*value);
            ++current;
        }
    }

    void push_back(T *data)
    {
        if (current == capacity)
        {
            T **temp = new T *[2 * capacity]
            { nullptr };
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = new T(*data);
        current++;
    }

    void erase(int index)
    {
        if (index < 0 || index >= current)
        {
            throw std::out_of_range("Index out of bounds");
        }

        delete arr[index];

        for (int i = index; i < current - 1; ++i)
        {
            arr[i] = arr[i + 1];
        }

        --current;
    }

    T *get(int index)
    {
        if (index < current)
            return arr[index];
        return nullptr;
    }

    void pop()
    {
        if (current > 0)
        {
            delete arr[current - 1];
            --current;
        }
    }

    int size() const { return current; }

    int getcapacity() const { return capacity; }

    void print() const
    {
        if (current == 0)
        {
            std::cout << "Vector is empty" << std::endl;
        }
        else
        {
            for (int i = 0; i < current; i++)
            {
                std::cout << *arr[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    T **begin() { return arr; }

    const T **begin() const { return arr; }

    T **end() { return arr + current; }
};
