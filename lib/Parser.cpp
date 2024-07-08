#include <stdexcept>
#include <string_view>
#include <string>
#include <iostream>

#include "Parser.hpp"


Parser::Parser(int argc, char** argv) : argc_(argc), argv_(argv), opt_() {}

Options Parser::Parse() {
    if (argc_ < 2) {
        throw std::invalid_argument("Not enough arguments!");
    }

    for (int i = 1; i < argc_; ++i) {
        std::string_view argument = argv_[i];
        if (argument.starts_with("--")) {
            ProcessLongArgument(argument);
        } else if (argument.starts_with("-")) {
            ProcessShortArgument(argument, i);
        } else if (opt_.filename.empty()) {
            opt_.filename = argument;
        } else {
            throw std::invalid_argument("Undefined argument: \"" + std::string(argument) + "\".");
        }
    }

    if (opt_.filename.empty()) {
        throw std::invalid_argument("Enter the file name as free argument!");
    }

    return opt_;
}


void Parser::ProcessLongArgument(const std::string_view& argument) {
    static const size_t kLinesArgumentEqualSignPosition = 8;
    static const size_t kDelimiterArgumentEqualSignPosition = 12;

    if (argument == "--tail") {
        opt_.tail = !opt_.tail;
    } else if (argument.starts_with("--lines=")) {
        opt_.lines = ConvertSubstringToInt(argument.substr(kLinesArgumentEqualSignPosition));
    } else if (argument.starts_with("--delimiter=")) {
        opt_.delimiter = ConvertToEscapeSubseq(argument.substr(kDelimiterArgumentEqualSignPosition));
    } else {
        throw std::invalid_argument("Error with parsing argument: \"" + std::string(argument) + "\".");
    }
}

void Parser::ProcessShortArgument(const std::string_view& argument, int& i) {
    if (argument == "-l") {
        if (i + 1 >= argc_) {
            throw std::invalid_argument("Missing value for argument -l");
        }
        opt_.lines = ConvertSubstringToInt(argv_[++i]);
    } else if (argument == "-d") {
        if (i + 1 >= argc_) {
            throw std::invalid_argument("Missing value for argument -d");
        }
        opt_.delimiter = ConvertToEscapeSubseq(argv_[++i]);
    } else if (argument == "-t") {
        opt_.tail = !opt_.tail;
    } else {
        throw std::invalid_argument("Invalid argument! Try --help.");
    }
}


char Parser::ConvertToEscapeSubseq(const std::string_view& subseq) {
    if (subseq.empty() || subseq[0] != '\\') {
        throw std::invalid_argument("Subsequence \"" + std::string(subseq) + "\" is not an escape subsequence symbol.");
    }

    switch (subseq[1]) {
        case 'n': return '\n';
        case 't': return '\t';
        case 'r': return '\r';
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'v': return '\v';
        default: return subseq[1];
    }
}

int Parser::ConvertSubstringToInt(const std::string_view& digit) {
    try {
        return std::stoi(std::string(digit));
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(std::string(digit) + " is not a valid number!");
    } catch (const std::out_of_range& e) {
        throw std::out_of_range(std::string(digit) + " is out of range!");
    }
}
