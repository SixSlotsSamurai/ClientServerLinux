#include "server.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>

Server::Server(int port) : port(port), logger("log.txt") {}

void Server::create_server_socket() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(server_socket, 5) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }
}

void Server::handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            close(client_socket);
            break;
        }

        buffer[bytes_received] = '\0';
        logger.log(buffer);
    }
}

void Server::start() {
    create_server_socket();
    std::cout << "Server listening on port " << port << std::endl;

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);

        if (client_socket != -1) {
            std::thread(&Server::handle_client, this, client_socket).detach();
        }
    }
}
