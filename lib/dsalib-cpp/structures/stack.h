#pragma once

#include "singly-linked-list.h"

template <typename Key>
class Stack {
private:
    SinglyLinkedList<Key> linked_list;

public:
    Stack() = default;

    int Size() const {
        return linked_list.Size();
    }

    bool Empty() const {
        return linked_list.Size() == 0;
    }

    void Push(Key key) {
        linked_list.PushFront(key);
    }

    Key Pop() {
        assert(linked_list.Size() > 0 && "Stack::Pop(): empty");
        return linked_list.PopFront();
    }

    Key Top() const {
        assert(linked_list.Size() > 0 && "Stack::Top(): empty");
        return linked_list.Front();
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack) {
        os << "Stack[ " << stack.linked_list << " ]";
        return os;
    }

    ~Stack() = default;
};
