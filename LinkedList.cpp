#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}
template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}
template <typename T>
int LinkedList<T>::get_head() const
{
    return head->data;
}

template <typename T>
void LinkedList<T>::push_back(T val)
{
    Node<T> *new_node = new Node<T>(val);

    if (head == nullptr)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }

    size++;
}

template <typename T>
Node<T> *LinkedList<T>::getNode(const int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Out of range");
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current;
}

template <typename T>
T &LinkedList<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Out of range");
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->data;
}

template <typename T>
void LinkedList<T>::push_front(T val)
{
    Node<T> *new_node = new Node<T>(val);

    if (head == nullptr)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }

    size++;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }

    Node<T> *current = head;
    Node<T> *previous = nullptr;

    while (current->next != nullptr)
    {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        previous->next = nullptr;
        tail = previous;
    }

    delete current;
    size--;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }

    Node<T> *current = head;
    head = head->next;

    delete current;
    size--;
}

template <typename T>
void LinkedList<T>::insert(T val, int index)
{
    if (index < 0 || index > size)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0)
    {
        push_front(val);
        return;
    }

    if (index == size)
    {
        push_back(val);
        return;
    }

    Node<T> *new_node = new Node<T>(val);
    Node<T> *current = head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    previous->next = new_node;
    new_node->next = current;

    size++;
}

template <typename T>
void LinkedList<T>::remove(int index)
{
}

template <typename T>
void LinkedList<T>::clear()
{
    while (head != nullptr)
    {
        pop_front();
    }
}

template <typename T>
int LinkedList<T>::get_size()
{
    return size;
}

template <typename T>
void LinkedList<T>::print()
{
    Node<T> *current = head;

    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << std::endl;
}

template <typename T>
void LinkedList<T>::reverse()
{
    Node<T> *current = head;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    tail = head;
    head = previous;
}

template <typename T>
void LinkedList<T>::sort()
{
    Node<T> *current = head;
    Node<T> *index = nullptr;
    T temp;

    if (head == nullptr)
    {
        return;
    }
    else
    {
        while (current != nullptr)
        {
            index = current->next;

            while (index != nullptr)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }

                index = index->next;
            }

            current = current->next;
        }
    }
}

template <typename T>
void LinkedList<T>::merge(LinkedList<T> &list)
{
    Node<T> *current = list.head;

    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

template <typename T>
void LinkedList<T>::isEmpty()
{
    if (head == nullptr)
    {
        std::cout << "List is empty" << std::endl;
    }
    else
    {
        std::cout << "List is not empty" << std::endl;
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
{
    Node<T> *current = list.head;

    while (current != nullptr)
    {
        os << current->data << " ";
        current = current->next;
    }

    return os;
}
