#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <thread>
#include "logger.h"

class Server {
public:
    Server(int port);
    void start();

private:
    int server_socket;
    int port;
    Logger logger;

    void handle_client(int client_socket);
    void create_server_socket();
};

#endif // SERVER_H
