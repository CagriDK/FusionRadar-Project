#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

enum class LogLevel {
    M_INFO,
    M_WARNING,
    M_ERROR,
};

class Logger {
public:
    Logger(const std::string& filename, const std::string& header = "");

    void log(const std::string& message, LogLevel level = LogLevel::M_INFO);

private:
    std::ofstream logFile;
    std::string getCurrentDateTime() const;
    std::string getLogLevelString(LogLevel level) const;
};

#endif // LOGGER_H
