#include <fstream>
#include <stdexcept>

#include "Options.hpp"
#include "PrintHelperAbstract.hpp"


class PrintHelperDefault : public PrintHelperAbstract {
public:
    PrintHelperDefault(Options opt) : PrintHelperAbstract(std::move(opt)) {}

    void Print() override {
        std::ifstream file(opt_.filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file \"" + opt_.filename + "\". Files must be in dir \"files\"!");
        }

        char* buffer = new char[kBufferSize];
        
        while (file.read(buffer, kBufferSize) || file.gcount() > 0) {
            size_t bytes_read = file.gcount();
            
            if (opt_.delimiter == '\n') {
                ProcessWithDefaultDelimiter(buffer, bytes_read);
            } else {
                ProcessWithNotDefaultDelimiter(buffer, bytes_read);
            }
        }

        delete[] buffer;
        file.close();
    }

private:
    uint64_t lines_amount_ = 0;

    void ProcessWithDefaultDelimiter(char* buffer, size_t bytes_read) {
        size_t i = 0;
        while (i < bytes_read && lines_amount_ < opt_.lines) {
            if (buffer[i] == '\n') {
                ++lines_amount_;
            }
            std::cout << buffer[i];

            ++i;
        }
    }

    void ProcessWithNotDefaultDelimiter(char* buffer, size_t bytes_read) {
        size_t i = 0;
        while (i < bytes_read && lines_amount_ < opt_.lines) {
            if (buffer[i] == '\n') {
                ++i; continue;
            }
            
            if (buffer[i] != opt_.delimiter) {
                std::cout << buffer[i];
            } else {
                std::cout << buffer[i] << "\n";
                ++lines_amount_;
            }

            ++i;
        }
    }
};