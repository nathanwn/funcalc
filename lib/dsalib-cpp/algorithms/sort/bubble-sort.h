#pragma once

#include "../../util/util.h"

namespace bubble_sort {
    template <typename T>
    void Sort(T a[], int begin, int end) {
        for (int i = begin; i < end - 1; i++) {
            bool sorted = true;
            for (int j = begin + 1; j < end - i; j++) {
                if (a[j - 1] > a[j]) {
                    util::swap(a[j - 1], a[j]);
                    sorted = false;
                }
            }
            if (sorted) break;
        }
    }
}
