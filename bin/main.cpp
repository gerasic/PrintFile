#include <iostream>

#include "lib/Options.hpp"
#include "lib/Parser.hpp"
#include "lib/Printer.hpp"


int main(int argc, char** argv) {
    Parser parser(argc, argv);

    Printer printer(parser.Parse());
    printer.Print();

    return 0;
}