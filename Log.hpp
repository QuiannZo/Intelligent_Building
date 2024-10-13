#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "FAT.hpp"

class Log {
protected:
    FAT* fileSystem;
    // Name of the file that contains the log
    std::string logFilename;
    // This variable is used to indicate how often should be saved the file system
    int saveFrequency;
    int saveCounter = 0;
    int defaultProcessId;
    std::string getCurrentDateTime();

public:
    Log(std::string logFilename, int defaultProcessId);
    ~Log();
    bool appendToLog(std::string text);
    bool appendToLogTimeHour(std::string text);
    std::string returnLog(std::string username);
    int getProcessId();
};



#endif