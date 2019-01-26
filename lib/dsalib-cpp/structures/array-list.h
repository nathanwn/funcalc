#pragma once

#include <cassert>
#include <iostream>

template <typename Key>
class ArrayList {
private:
    int capacity;
    Key* keys;
    int size;

    void Reallocate() {
        Key* old_keys = keys;
        keys = new Key[capacity * 2];
        for (int i = 0; i < capacity; i++) {
            keys[i] = old_keys[i];
        }
        capacity *= 2;
        delete [] old_keys;
    }

public:
    ArrayList() {
        capacity = 1;
        size = 0;
        keys = new Key[capacity];
    }

    int Size() const {
        return size;
    }

    void PushBack(Key key) {
        if (size == capacity) {
            Reallocate();
        }
        keys[size] = key;
        size++;
    }

    Key PopBack() {
        assert(size > 0 && "ArrayList::popBack(): empty list");
        size--;
        Key key = keys[size];
    }

    Key& operator[](int index) {
        assert(index > -1 && index < size && "ArrayList::operator[]: out-of-bound");
        return keys[index];
    }

    Key operator[](int index) const {
        assert(index > -1 && index < size && "ArrayList::operator[]: out-of-bound");
        return keys[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& arrayList) {
        os << "ArrayList[ ";
        os << "size = " << arrayList.size << ", ";
        os << "keys = [ ";
        for (int i = 0; i < arrayList.size; i++) {
            os << arrayList[i] << ' ';
        }
        os << "] ]";
        return os;
    }

    ~ArrayList() {
        delete [] keys;
    }
};
