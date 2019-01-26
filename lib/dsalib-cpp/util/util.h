#pragma once

#include <string>

namespace util {
    template <typename T>
    void swap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <typename T>
    T min(T& a, T& b) {
        if (a < b) return a;
        return b;
    }

    template <typename T>
    T max(T& a, T& b) {
        if (a > b) return a;
        return b;
    }

    bool IsUpperCase(const char& c) {
        return 'A' <= c && c <= 'Z';
    }

    bool IsLowerCase(const char& c) {
        return 'a' <= c && c <= 'z';
    }

    bool IsLetter(const char& c) {
        return IsUpperCase(c) || IsLowerCase(c);
    }

    bool IsDigit(const char& c) {
        return '0' <= c && c <= '9';
    }

    void RemoveSpaces(std::string& s) {
        std::string res;
        for (char c : s) {
            if (c == ' ') continue;
            res += c;
        }
        s = res;
    }

    template <typename T>
    void PrintArray(T a[], int begin, int end) {
        for (int i = begin; i < end; i++) {
            std::cout << a[i] << ' ';
        }
        std::cout << '\n';
    }
};

