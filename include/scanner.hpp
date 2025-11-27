#pragma once
#include <string>
#include <vector>

class Scanner {
public:
    Scanner(const std::string &target, const std::vector<int> &ports);
    void run();

private:
    std::string target;
    std::vector<int> ports;

    bool check_port(int port);
};
