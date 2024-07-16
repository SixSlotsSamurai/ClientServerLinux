#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(const std::string& name, const std::string& server_ip, int port, int interval);
    void start();

private:
    std::string name;
    std::string server_ip;
    int port;
    int interval;

    void send_message();
};

#endif // CLIENT_H
