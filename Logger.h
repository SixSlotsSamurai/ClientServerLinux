#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>
#include <string>

class Logger {
public:
    Logger(const std::string& filename) : log_file(filename, std::ios_base::app) {}

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_file << message << std::endl;
    }

private:
    std::ofstream log_file;
    std::mutex log_mutex;
};

#endif // LOGGER_H
