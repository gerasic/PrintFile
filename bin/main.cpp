#include <iostream>

#include "lib/Parser.hpp"
#include "lib/Printer.hpp"


int main(int argc, char** argv) {
    Parser parser(argc, argv);
    Options opt = parser.Parse();
    opt.Print();

    Printer printer(opt);
    printer.Print();

    return 0;
}