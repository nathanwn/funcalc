#pragma once

#include "../../util/util.h"

namespace quick_sort {
    template <typename T>
    int Partition(T a[], int begin, int end) {
        T pivot_key = a[end - 1];
        int pivot = begin;

        for (int i = begin; i < end - 1; i++) {
            if (a[i] < pivot_key) {
                util::swap(a[i], a[pivot]);
                pivot++;
            }
        }

        util::swap(a[pivot], a[end - 1]);

        return pivot;
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        if (begin < end - 1) {
            int pivot = Partition(a, begin, end);
            Sort(a, begin, pivot);
            Sort(a, pivot, end);
        }
    }
};
