#pragma once

namespace counting_sort {
    template <typename T>
    void Sort(T a[], int begin, int end, int range) {
        int f[range + 1];
        for (int i = 0; i <= range; i++) {
            f[i] = 0;
        }
        for (int i = begin; i < end; i++) {
            ++f[a[i]];
        }
        int j = 0;
        for (int i = 0; i <= range; i++) {
            while (f[i] > 0) {
                a[j] = i;
                ++j;
                --f[i];
            }
        }
    }
};
