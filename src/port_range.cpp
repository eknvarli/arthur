#include "port_range.hpp"
#include "util.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

PortRange::PortRange(const std::string &input) {
    parse(input);
}

void PortRange::parse(const std::string &input) {
    std::stringstream ss(input);
    std::string segment;

    while (std::getline(ss, segment, ',')) {
        if (segment.find('-') != std::string::npos) {
            auto dash_pos = segment.find('-');
            std::string start = segment.substr(0, dash_pos);
            std::string end = segment.substr(dash_pos + 1);

            if (!util::is_number(start) || !util::is_number(end))
                throw std::runtime_error("Invalid port range: " + segment);

            int s = std::stoi(start);
            int e = std::stoi(end);

            if (s > e) std::swap(s, e);

            for (int p = s; p <= e; p++)
                ports.push_back(p);
        } else {
            if (!util::is_number(segment))
                throw std::runtime_error("Invalid port: " + segment);

            ports.push_back(std::stoi(segment));
        }
    }
}

std::vector<int> PortRange::get_ports() const {
    return ports;
}