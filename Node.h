#pragma once

template <typename T>
class Node
{
public:
    T dataNode;
    Node *next;

    Node(T val);
};
