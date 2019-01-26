#pragma once

#include <cassert>
#include "avl-tree.h"
#include "array-list.h"

template <typename T>
class TreeSet {
private:
    AVLTree<T> tree;
    int size;

public:
    TreeSet() : size(0) {}

    int Size() const {
        return size;
    }

    void Push(T key) {
        tree.Push(key);
        size++;
    }

    void Pop(T key) {
        assert(tree.Has(key) && "TreeSet::Pop(): invalid key");
        tree.Pop(key);
        size--;
    }

    bool Has(T key) const {
        return tree.Has(key);
    }

    T Min() {
        return tree.Min();
    }

    T Max() {
        return tree.Max();
    }

    ArrayList<T> Entries() {
        return tree.GetArrayList();
    }

    ~TreeSet() = default;
};
