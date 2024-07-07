#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>

struct Options {
    uint64_t lines = __UINT64_MAX__;
    bool tail = false;
    char delimiter = '\n';
};

#endif // OPTIONS_H