#pragma once

#include "../../util/util.h"

namespace heap_sort {
    template <typename T>
    void Heapify(T heap[], int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < n && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != i) {
            util::swap(heap[i], heap[largest]);
            Heapify(heap, n, largest);
        }
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        int n = end - begin;
        T heap[n];
        for (int i = 0; i < n; i++) {
            heap[i] = a[begin + i];
        }
        for (int i = n / 2 - 1; i > -1; i--) {
            Heapify(heap, n, i);
        }
        for (int i = n - 1; i > -1; i--) {
            util::swap(heap[0], heap[i]);
            Heapify(heap, i, 0);
        }
        for (int i = 0; i < n; i++) {
            a[begin + i] = heap[i];
        }
    }
};
