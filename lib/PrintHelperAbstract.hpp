#pragma once

#include <fstream>
#include <stdexcept>

#include "Options.hpp"


class PrintHelperAbstract {
public:
    PrintHelperAbstract(Options opt) : opt_(std::move(opt)) {}
    virtual void Print() = 0;

    virtual ~PrintHelperAbstract() = default; 
protected:
    Options opt_;
    const size_t kBufferSize = 4096;
};
