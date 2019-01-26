#pragma once

namespace binary_search {
    template <typename T>
    int search(T a[], int begin, int end, T key) {
        --end;
        int mid = (begin + end) / 2;
        while (begin < end && a[mid] != key) {
             if (a[mid] < key) {
                 begin = mid + 1;
             } else {
                 end = mid - 1;
             }
             mid = (begin + end) / 2;
        }
        return (a[mid] == key) ? (mid) : (-1);
    }

    /**
     * lower_bound: found the position of the leftmost element that is
     *              less than or equal to key
     */
    template <typename T>
    int lower_bound(T a[], int begin, int end, T key) {
        while (begin < end) {
            int mid = (begin + end) / 2;
            if (a[mid] >= key) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }
        return begin;
    }

    /**
     * upper_bound: found the position of the leftmost element that is
     *              strictly greater than key
     */
     template <typename T>
     int upper_bound(T a[], int begin, int end, T key) {
         while (begin < end) {
             int mid = (begin + end) / 2;
             if (a[mid] <= key) {
                 begin = mid + 1;
             } else {
                 end = mid;
             }
         }
         return begin;
     }
}
