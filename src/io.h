#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include "../lib/dsalib-cpp/structures/array-list.h"
#include "console.h"

namespace io {
    ArrayList<std::string> ReadConsoleLines() {
        console::DrawLine();
        std::cout << "Please input the number of lines\n";
        std::cout << "=> ";
        int num_lines;
        while (true) {
            std::cin >> num_lines;
            if (!std::cin.good()) {
                std::cin.clear(); // clear the cin's error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // clear the current line
                std::cout << "Error: invalid choice. Please input your choice again\n";
                std::cout << "=> ";
            }
            else break;
        }

        ArrayList<std::string> lines;

        for (int i = 0; i < num_lines; i++) {
            std::string line;
            std::getline(std::cin, line);
            lines.PushBack(line);
        }

        return lines;
    }

    ArrayList<std::string> ReadFileLines(std::ifstream& in_file_stream) {
        ArrayList<std::string> lines;
        std::string line;

        while (std::getline(in_file_stream, line)) {
            lines.PushBack(line);
        }

        return lines;
    }

    ArrayList<std::string> ReadLines() {
        std::cout << "Choose how you want to input expressions:\n";
        std::cout << "1. Using the console\n";
        std::cout << "2. Using text file\n";
        std::cout << "=> ";
        int choice;

        while (true) {
            std::cin >> choice;

            if (!std::cin.good()) {
                std::cin.clear(); // clear the cin's error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // clear the current line
                std::cout << "Error: invalid choice. Please input your choice again\n";
                std::cout << "=> ";
            }
            else if (choice != 1 && choice != 2) {
                std::cout << "Error: invalid choice. Please input your choice again\n";
                std::cout << "=> ";
            }
            else break;
        }

        if (choice == 1) {
            return ReadConsoleLines();
        }

        console::DrawLine();
        std::cout << "Input the input file (both relative or absolute path can be used)\n";
        std::ifstream infile_stream;

        while (true) {
            std::string file_path;
            std::cout << "=> ";
            std::cin >> file_path;
            infile_stream.open(file_path);
            if (!infile_stream.good()) {
                std::cout << "Error: could not open file " << file_path << '\n';
                infile_stream.close();
            }
            else break;
        }

        console::DrawLine();
        return ReadFileLines(infile_stream);
    }
}

