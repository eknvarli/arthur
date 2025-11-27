#pragma once
#include <vector>
#include <string>

class PortRange {
public:
    explicit PortRange(const std::string &input);
    std::vector<int> get_ports() const;

private:
    std::vector<int> ports;
    void parse(const std::string &input);
};
