#pragma once

#include <iostream>

namespace console {
    const int LINE_LENGTH = 12;

    void DrawLine() {
        for (int i = 0; i < LINE_LENGTH; i++) {
            std::cout << "_";
        }
        std::cout << "\n\n";
    }
};
