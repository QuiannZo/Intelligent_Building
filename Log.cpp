#include "Log.hpp"

Log::Log(std::string logFilename, int defaultProcessId) 
    : logFilename(logFilename), defaultProcessId(defaultProcessId) {
    this->fileSystem = new FAT();
    bool fileCreated = false;
    bool error = false;
    // Try opening the file in read mode to check if it exists
    std::ifstream fileCheck(logFilename.c_str());
    if (fileCheck) {
        std::cout << "File already exists, it will be loaded into the file system." << std::endl;
        fileCheck.close();
    } else {
        // Create the file if it doesn't exist
        std::ofstream file(logFilename);
        if (file) {
            std::cout << "File created: " << logFilename << std::endl;
            file.close();
            fileCreated = true;
        } else {
            std::cerr << "Error creating file!" << std::endl;
            error = true;
        }
    }
    // load file into our filesystem 
    if (!error) {
        std::ostringstream output;
        if (this->fileSystem->loadFile((char*)logFilename.c_str(), defaultProcessId)) {
            if (fileCreated) {
                output << "File '" << logFilename << "' <Type:Log> created and loaded into filesystem.";
            } else {
                output << "File '" << logFilename << "' <Type:Log> loaded into filesystem.";
            }   
            this->fileSystem->open((char*)logFilename.c_str(), defaultProcessId);
            if (!this->appendToLogTimeHour(output.str())) {
                std::cerr << "Error: could not append to LOG '" << logFilename << "'."  << std::endl;
            }
        } else {
            std::cerr << "Error: FAT<filesystem> could not open file " << logFilename << std::endl;
        }
    }
}

Log::~Log() {
    // save log before destroy object 
    this->fileSystem->saveFile((char*)logFilename.c_str(), defaultProcessId, (char*)logFilename.c_str());
    this->fileSystem->close((char*)logFilename.c_str(), defaultProcessId);
    std::ostringstream output;
    output << "Filesystem <FAT> closed and saved to file '" << logFilename << "'.";
    this->appendToLogTimeHour(output.str());
    delete this->fileSystem;
}

bool Log::appendToLog(std::string text) {
    return this->fileSystem->append((char*)logFilename.c_str(), this->getProcessId(), (char*)text.c_str()) << '\n';
}

bool Log::appendToLogTimeHour(std::string text) {
    std::ostringstream output;
    std::string dateTime = this->getCurrentDateTime();
    output << dateTime << " : " << text << '\n';
    return this->fileSystem->append((char*)logFilename.c_str(), this->getProcessId(), (char*)output.str().c_str());
}

std::string Log::returnLog(std::string username) {
    std::string completeFile;
    std::ostringstream logEntry;
    if(this->fileSystem->getCompleteFile((char*)logFilename.c_str(), this->getProcessId(), completeFile)) {
        logEntry << "User '" << username << "' gets access to entire LOG ('" << this->logFilename << "')."; 
        this->appendToLogTimeHour(logEntry.str());
    } else {
        logEntry << "Error: user '" << username << "' cannot get access to LOG ('" << this->logFilename << "')."; 
        this->appendToLogTimeHour(logEntry.str());
    }
    return completeFile;
}

int Log::getProcessId() {
    return this->defaultProcessId;
}

std::string Log::getCurrentDateTime() {
    // Get the current time
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    // Create a stringstream to format the output
    std::ostringstream time;
    time << std::put_time(localTime, "%d/%m/%Y - %H:%M:%S");

    return time.str();
}
