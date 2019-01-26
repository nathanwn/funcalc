#pragma once

#include <iostream>
#include "array-list.h"
#include "../util/util.h"

template <typename Key>
class Heap {
private:
    ArrayList<Key> keys;

    int Parent(int i) {
        return (i - 1) / 2;
    }

    int Left(int i) {
        return i * 2 + 1;
    }

    int Right(int i) {
        return i * 2 + 2;
    }

    void SwapKeys(int i, int j) {
        util::swap(keys[i], keys[j]);
    }

    void Heapify(int i) {
        int smallest = i;
        int left = Left(i);
        int right = Right(i);
        if (left < keys.Size() && keys[left] < keys[smallest]) {
            smallest = left;
        }
        if (right < keys.Size() && keys[right] < keys[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            SwapKeys(i, smallest);
            Heapify(smallest);
        }
    }

public:
    bool Empty() {
        return keys.Size() == 0;
    }

    void Build(Key* a, int n) {
        for (int i = 0; i < n; i++) {
            keys.PushBack(a[i]);
        }
        for (int i = keys.Size() / 2; i > -1; i--) {
            Heapify(i);
        }
    }

    void Push(Key key) {
        keys.PushBack(key);
        int i = keys.Size() - 1;
        int parent = Parent(i);
        while (i > 0 && keys[i] < keys[parent]) {
            SwapKeys(i, parent);
            i = parent;
            parent = Parent(i);
        }
    }

    Key Pop() {
        assert(keys.Size() > 0 && "Heap::top(): heap is empty");
        int top = keys[0];
        keys[0] = keys[keys.Size() - 1];
        keys.PopBack();
        Heapify(0);
        return top;
    }

    Key Top() {
        assert(keys.Size() > 0 && "Heap::top(): heap is empty");
        return keys[0];
    }

    friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
        os << heap.keys;
        return os;
    }
};
