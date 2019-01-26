#pragma once

#include "../../util/util.h"

namespace merge_sort {
    template <typename T>
    void Merge(T a[], int begin, int mid, int end) {
        int n_left = mid - begin;
        int n_right = end - mid;

        T left[n_left];
        T right[n_right];

        for (int i = 0; i < n_left; i++) {
            left[i] = a[begin + i];
        }
        for (int i = 0; i < n_right; i++) {
            right[i] = a[mid + i];
        }

        int l = 0;
        int r = 0;

        for (int i = begin; i < end; i++) {
            if (l == n_left) {
                a[i] = right[r];
                r++;
            }
            else if (r == n_right) {
                a[i] = left[l];
                l++;
            }
            else if (left[l] < right[r]) {
                a[i] = left[l];
                l++;
            }
            else {
                a[i] = right[r];
                r++;
            }
        }
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        if (begin < end - 1) {
            int mid = (begin + end) / 2;
            Sort(a, begin, mid);
            Sort(a, mid, end);
            Merge(a, begin, mid, end);
        }
    }
};
