#include <iostream>
#include "util.hpp"
#include "port_range.hpp"
#include "scanner.hpp"

int main(int argc, char** argv) {
    util::print_banner();

    if (argc < 3) {
        std::cout << "Usage: ./arthur <IP> <PORTS>\n";
        std::cout << "Example: ./arthur 192.168.1.10 80,443,1000-2000\n";
        return 1;
    }

    std::string target = argv[1];
    std::string range = argv[2];

    try {
        PortRange pr(range);
        Scanner scanner(target, pr.get_ports());
        scanner.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}