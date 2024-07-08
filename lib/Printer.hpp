#include "Options.hpp"


class Printer {
public:
    Printer(Options opt);
    void Print();
private:
    Options opt_;
};