#include "logger.h"
#include <chrono>

Logger::Logger(const std::string& filename, const std::string& header) {
    std::string logFolder = "Log";
    std::filesystem::path logFolderPath = std::filesystem::current_path() / logFolder;

    if (!std::filesystem::exists(logFolderPath)) {
        std::filesystem::create_directory(logFolderPath);
    }

    std::string filePath = logFolder + "/" + filename + ".csv";

    std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);
    if (!fileStream) {
        // File does not exist or cannot be opened, create a new file
        logFile.open(filePath);
        if (!logFile) {
            std::cerr << "Failed to create log file." << std::endl;
            return;
        }
        logFile << header << std::endl;
    } else {
        // File exists, check if it is empty
        std::streampos fileSize = fileStream.tellg();
        fileStream.close();

        if (fileSize != 0) {
            // File is empty, truncate it and write the header
            logFile.open(filePath, std::ios::trunc);
            if (!logFile) {
                std::cerr << "Failed to open log file." << std::endl;
                return;
            }
            logFile << header << std::endl;
        }
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    std::string timestamp = getCurrentDateTime();
    std::string levelStr = getLogLevelString(level);

    std::string logMessage = "[" + timestamp + "] [" + levelStr + "]: " + message;

    std::cout << logMessage << std::endl;
    logFile << logMessage << std::endl;
}

std::string Logger::getCurrentDateTime() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::string dateTime(std::ctime(&time));
    dateTime.pop_back(); // Remove newline character

    return dateTime;
}

std::string Logger::getLogLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::M_INFO:
            return "M_INFO";
        case LogLevel::M_WARNING:
            return "M_WARNING";
        case LogLevel::M_ERROR:
            return "M_ERROR";
        default:
            return "";
    }
}
