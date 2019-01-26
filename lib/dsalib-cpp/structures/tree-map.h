#pragma once

#include <cassert>
#include "avl-tree.h"
#include "key-value-pair.h"

template <typename Key, typename Value>
class TreeMap {
    using KeyValuePair = KeyValuePair<Key, Value>;

private:
    AVLTree<KeyValuePair> tree;
    int size;

public:
    TreeMap() : size(0) {}

    int Size() const {
        return size;
    }

    void Push( Key key, Value value) {
        tree.Push(KeyValuePair(key, value));
        size++;
    }

    void Pop(Key key) {
        KeyValuePair ref_entry(key);
        assert(tree.Has(ref_entry) && "TreeMap::Pop(): invalid key");
        tree.Pop(ref_entry);
        size--;
    }

    bool Has(Key key) const {
        KeyValuePair ref_entry(key);
        return tree.Has(ref_entry);
    }

    Value Get(Key key) const {
        KeyValuePair ref_entry(key);
        return tree.Get(ref_entry).value;
    }

    Value Min() const {
        return tree.Min().value;
    }

    Value Max() const {
        return tree.Max().value;
    }

    ArrayList<KeyValuePair> Entries() {
        return tree.GetArrayList();
    }

    ~TreeMap() = default;
};
