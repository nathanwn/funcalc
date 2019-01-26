#pragma once

namespace shell_sort {
    template <typename T>
    void Phase(T a[], int begin, int end, int gap) {
        for (int i = begin + gap; i < end; i += gap) {
            int x = a[i];
            int j;
            for (j = i - gap; j > -1 && a[j] > x; j -= gap) {
                a[j + gap] = a[j];
            }
            a[j + gap] = x;
        }
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        int n = (end - begin) / 2;
        for (int gap = n; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                Phase(a, begin, end, gap);
            }
        }
    }
};
