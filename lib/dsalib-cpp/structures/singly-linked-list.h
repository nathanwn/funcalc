#pragma once

#include <iostream>

template <typename Key>
struct SinglyLinkedListNode {
    Key key;
    SinglyLinkedListNode* next;

    SinglyLinkedListNode() = default;

    SinglyLinkedListNode(Key key) : key(key) {}

    static SinglyLinkedListNode* createNil() {
        auto nil = new SinglyLinkedListNode();
        nil->next = nil;
        return nil;
    }
};

template <typename Key>
class SinglyLinkedList {
private:
    using Node=SinglyLinkedListNode<Key>;

    Node* nil;
    int size;

public:
    SinglyLinkedList() {
        nil = Node::createNil();
        size = 0;
    }

    int Size() const {
        return size;
    }

    void PushFront(Key key) {
        auto front = new Node(key);
        front->next = nil->next;
        nil->next = front;
        size++;
    }

    Key PopFront() {
        assert(size > 0 && "SinglyLinkedList::PopFront(): empty");
        auto front = nil->next;
        Key key = front->key;
        nil->next = front->next;
        delete front;
        size--;
        return key;
    }

    Key Front() const {
        return nil->next->key;
    }

    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList& singly_linked_list) {
        os << "SinglyLinkedList[ ";
        os << "size = " << singly_linked_list.size << ", ";
        os << "keys = [ ";
        auto curr = singly_linked_list.nil->next;
        while (curr != singly_linked_list.nil) {
            os << curr->key << ' ';
            curr = curr->next;
        }
        os << "]";
        return os;
    }

    ~SinglyLinkedList() {
        auto curr = nil->next;
        while (curr != nil) {
            auto next = curr->next;
            delete curr;
            curr = next;
        }
        delete curr;
    }
};