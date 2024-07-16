#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: server <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);

    try {
        Server server(port);
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
