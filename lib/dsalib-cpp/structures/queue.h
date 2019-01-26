#pragma once

#include <cassert>
#include "doubly-linked-list.h"

template <typename Key>
class Queue {
private:
    DoublyLinkedList<Key> linked_list;

public:
    Queue() = default;

    int Size() const {
        return linked_list.Size();
    }

    bool Empty() const {
        return linked_list.Size() == 0;
    }

    void Enqueue(Key key) {
        linked_list.PushBack(key);
    }

    Key Dequeue() {
        assert(linked_list.Size() > 0 && "Queue::dequeue(): empty");
        return linked_list.PopFront();
    }

    Key Front() const {
        assert(linked_list.Size() > 0 && "Queue::getTop(): empty");
        return linked_list.Front();
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
        os << "Queue[ " << queue.linked_list << " ]";
        return os;
    }

    ~Queue() = default;
};