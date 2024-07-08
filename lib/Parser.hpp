#include "Options.hpp"

class Parser {
public:
    Parser(int argc, char** argv);
    Options Parse();
private:
    int argc_;
    char** argv_;
    Options opt_;

    void ProcessShortArgument(const std::string_view& argument, int& i);
    void ProcessLongArgument(const std::string_view& argument);

    char ConvertToEscapeSubseq(const std::string_view& subseq);
    int ConvertSubstringToInt(const std::string_view& digit);
};