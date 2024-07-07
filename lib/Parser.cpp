#include "Parser.hpp"

Parser::Parser(int argc, char** argv) : argc_(argc), argv_(argv) {}

Options Parser::Parse() {
    return Options{};
}