#include "scanner.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

static std::mutex print_mutex;

Scanner::Scanner(const std::string &target, const std::vector<int> &ports)
    : target(target), ports(ports) {}

bool Scanner::check_port(int port) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(target.c_str());

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    bool open = connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0;

#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif

    return open;
}

void Scanner::run() {
    std::vector<std::thread> threads;

    for (int port : ports) {
        threads.emplace_back([&, port]() {
            if (check_port(port)) {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "[OPEN]  Port " << port << "\n";
            } else {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "[CLOSED] Port " << port << "\n";
            }
        });
    }

    for (auto &t : threads)
        t.join();
}
