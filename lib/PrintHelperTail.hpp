#include <fstream>
#include <stdexcept>

#include "Options.hpp"
#include "PrintHelperAbstract.hpp"


class PrintHelperTail : public PrintHelperAbstract {
public:
    PrintHelperTail(Options opt) : PrintHelperAbstract(std::move(opt)) {}

    void Print() override {
        std::ifstream file(opt_.filename, std::ios::binary | std::ios::ate);
        if (!file) {
            throw std::runtime_error("Failed to open file \"" + opt_.filename + "\". Files must be in dir \"files\"!");
        }

        size_t file_size = static_cast<size_t>(file.tellg()); 

        char* buffer = new char[kBufferSize]; 
      
        for (size_t offset = file_size; offset > 0; ) {
            size_t bytes_read = std::min(kBufferSize, offset); 
            offset -= bytes_read; 
            file.seekg(offset);

            if (!file.read(buffer, bytes_read)) {
                throw std::runtime_error("Error with reading file \"" + opt_.filename + "\".");
            }

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
    void ProcessWithDefaultDelimiter(char* buffer, ssize_t bytes_read) {
        static size_t count_lines = 0;
        --bytes_read;

        while (bytes_read >= 0 && count_lines < opt_.lines) {
            if (buffer[bytes_read] == '\n') {
                ++count_lines;
            }

            std::cout << buffer[bytes_read];
            --bytes_read;
        }
    }

    void ProcessWithNotDefaultDelimiter(char* buffer, ssize_t bytes_read) {
        static size_t count_lines = 0;
        --bytes_read;

        while (bytes_read >= 0 && count_lines < opt_.lines) {
            if (buffer[bytes_read] == '\n') {
                --bytes_read; continue;
            }

            if (buffer[bytes_read] == opt_.delimiter) {
                std::cout << buffer[bytes_read] << '\n';
                ++count_lines;
            } else {
                std::cout << buffer[bytes_read];
            }

            --bytes_read;
        }
    }
};