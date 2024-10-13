#ifndef DATA_COLLECTOR_HPP
#define DATA_COLLECTOR_HPP

#include "Log.hpp"

class DataCollector : public Log {
private:
    std::string sensorFilename;
public:
    DataCollector(std::string logFilename, int processId, std::string sensorFilename);
    ~DataCollector();
    std::string returnSensorFile(std::string username);
};

#endif