#pragma once

#include "../../util/util.h"

namespace selection_sort {
    /**
     * @tparam T
     * @param a     array
     * @param begin the start index of the array
     * @param end   the end index of the array (exclusive)
     * @return index of the smallest element in the segment [begin, end)
     */
    template <typename T>
    int MinIndex(T a[], int begin, int end) {
        int min_index = begin;
        for (int i = begin + 1; i < end; i++) {
            if (a[i] < a[min_index]) {
                min_index = i;
            }
        }
        return min_index;
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        for (int i = 0; i < end - 1; i++) {
            int j = MinIndex(a, i + 1, end); // O(n)
            util::swap(a[i], a[j]);
        }
    }
};