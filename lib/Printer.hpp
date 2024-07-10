#include "Options.hpp"

#include "PrintHelperDefault.hpp"
#include "PrintHelperTail.hpp"

class Printer {
public:
    Printer(Options opt) {
        if (opt.tail) {
            print_helper_ = std::make_unique<PrintHelperTail>(std::move(opt));
        } else {
            print_helper_ = std::make_unique<PrintHelperDefault>(std::move(opt));
        }
    }

    void Print() {
        print_helper_->Print();
    }

private:
    std::unique_ptr<PrintHelperAbstract> print_helper_;
};