#include "util.hpp"
#include <iostream>
#include <algorithm>

namespace util {

bool is_number(const std::string &s) {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(), ::isdigit);
}

void print_banner() {
    std::cout << R"(
    -----------------------------------------
                ARTHUR PORT SCANNER
    -----------------------------------------
    )" << "\n";
}

}
