#include "client.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

Client::Client(const std::string& name, const std::string& server_ip, int port, int interval)
    : name(name), server_ip(server_ip), port(port), interval(interval) {}

void Client::send_message() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        close(client_socket);
        throw std::runtime_error("Invalid address/ Address not supported");
    }

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(client_socket);
        throw std::runtime_error("Connection failed");
    }

    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "[%Y-%m-%d %H:%M:%S") << "." << (milliseconds % 1000) << "] " << name;

    std::string message = oss.str();
    send(client_socket, message.c_str(), message.size(), 0);

    close(client_socket);
}

void Client::start() {
    while (true) {
        send_message();
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}
