#pragma once

namespace radix_sort {
    template <typename T>
    T Max(T a[], int begin, int end) {
        T max_value = a[begin];

        for (int i = begin + 1; i < end; i++) {
            if (max_value < a[i]) {
                max_value = a[i];
            }
        }

        return max_value;
    }

    template <typename T>
    void CountingSort(T a[], int begin, int end, int exp) {
        int n = end - begin;
        int f[10];
        int digit[n];
        int holder[n];

        for (int i = 0; i < 10; i++) {
            f[i] = 0;
        }

        for (int i = begin; i < end; i++) {
            digit[i - begin] = (a[i] / exp) % 10;
            f[digit[i - begin]]++;
        }

        // Turn frequency into position
        --f[0];
        for (int i = 1; i < 10; i++) {
            f[i] += f[i - 1];
        }

        for (int i = end - 1; i >= begin; i--) {
            holder[f[digit[i - begin]]] = a[i];
            --f[digit[i - begin]];
        }

        for (int i = begin; i < end; i++) {
            a[i] = holder[begin + i];
        }
    }

    template <typename T>
    void Sort(T a[], int begin, int end) {
        int n = end - begin;

        T max_value = Max(a, begin, end);
        int max_num_digits = 0;

        while (max_value > 0) {
            max_value /= 10;
            ++max_num_digits;
        }

        int exp = 1;

        for (int i = 1; i <= max_num_digits; i++) {
            CountingSort(a, begin, end, exp);
            exp *= 10;
        }
    }
};
