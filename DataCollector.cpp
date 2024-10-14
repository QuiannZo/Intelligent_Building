#include "DataCollector.hpp"

DataCollector::DataCollector(std::string logFilename, int processId, std::string sensorFilename) 
: Log(logFilename, processId), sensorFilename(sensorFilename)  {
    bool fileCreated = false;
    bool error = false;
    // Try opening the file in read mode to check if it exists
    std::ifstream fileCheck(sensorFilename.c_str());
    if (fileCheck) {
        fileCheck.close();
        std::cout << "File '" << sensorFilename << "' already exists, it will be loaded into the file system." << std::endl;
    } else {
        // Create the file if it doesn't exist
        std::ofstream file(sensorFilename);
        if (file) {
            file.close();
            std::cout << "File created: " << sensorFilename << std::endl;
            fileCreated = true;
        } else {
            std::cerr << "Error creating file: " << sensorFilename << std::endl;
            error = true;
        }
    }
    // load file into our filesystem 
    if (!error) {
        std::ostringstream output;
        if (this->fileSystem->loadFile((char*)sensorFilename.c_str(), processId)) {
            if (fileCreated) {
                output << "File '" << sensorFilename << "' <Type:File-sensor-data> created and loaded into filesystem.";
            } else {
                output << "File '" << sensorFilename << "' <Type:File-sensor-data> loaded into filesystem.";
            }
            if(!this->fileSystem->open((char*)sensorFilename.c_str(), defaultProcessId)) {
                std::cerr << "Error <filesystem>: could not open file '" <<  sensorFilename << "'.\n";
            } else {
                if (fileCreated) {
                    if (!this->fileSystem->append((char*)sensorFilename.c_str(), this->getProcessId() 
                        ,(char*)"idSensor,date,time,value\n")) {
                            std::cerr << "Error: could not append to '" << sensorFilename << "'."  << std::endl;
                        }
                }
            }
            if (!this->appendToLogTimeHour(output.str())) {
                std::cerr << "Error: could not append to '" << logFilename << "'."  << std::endl;
            }
        } else {
            std::cerr << "Error: could not open file " << sensorFilename << std::endl;
        }
    }
}

DataCollector::~DataCollector() {
    // save log before destroy object 
    this->fileSystem->saveFile((char*)sensorFilename.c_str(), defaultProcessId, (char*)sensorFilename.c_str());
    this->fileSystem->close((char*)sensorFilename.c_str(), defaultProcessId);
    std::ostringstream output;
    output << "Sensor data file closed and saved to file '" << sensorFilename << "'.";
    this->appendToLogTimeHour(output.str());
}

std::string DataCollector::returnSensorFile(std::string username) {
    std::string completeFile;
    std::ostringstream logEntry;
    if(this->fileSystem->getCompleteFile((char*)sensorFilename.c_str(), this->getProcessId(), completeFile)) {
        logEntry << "User '" << username << "' gets access to complete sensor information in '" << this->sensorFilename << "' file."; 
        this->appendToLogTimeHour(logEntry.str());
    } else {
        logEntry << "Error: user '" << username << "' cannot get access to sensor data file ('" << this->sensorFilename << "')."; 
        this->appendToLogTimeHour(logEntry.str());
    }
    return completeFile;
    return std::string();
}
