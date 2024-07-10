#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>
#include <string>
#include <iostream>

struct Options {
    uint64_t lines = __UINT64_MAX__;
    bool tail = false;
    char delimiter = '\n';
    std::string filename;

    void Print() {
        std::cout << "lines = " << lines << "\n";
        std::cout << "tail = " << tail << "\n";
        std::cout << "filename = " << filename << "\n";
        std::cout << "delimiter = ";
        if (delimiter == '\n') {
            std::cout << "\\n" << "\n";
        } else if (delimiter == '\t') {
            std::cout << "\\t" << "\n";
        } else if (delimiter == '\r') {
            std::cout << "\\r" << "\n";
        } else if (delimiter == '\a') {
            std::cout << "\\a" << "\n";
        } else if (delimiter == '\b') {
            std::cout << "\\b" << "\n";
        } else if (delimiter == '\f') {
            std::cout << "\\f" << "\n";
        } else {
            std::cout << delimiter << "\n";
        }
    }
};

#endif // OPTIONS_H