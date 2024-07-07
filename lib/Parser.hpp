#include "Options.hpp"

class Parser {
public:
    Parser(int argc, char** argv);
    Options Parse();
private:
    int argc_;
    char** argv_;
};