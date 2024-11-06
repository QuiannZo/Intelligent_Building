#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "DataNode.hpp"

// Constructor
DataNode::DataNode(std::string logFilename, int processId, std::string sensorFilename, int port) 
: Node(logFilename, processId, port)  {
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

DataNode::~DataNode() {
    // save log before destroy object 
    this->fileSystem->saveFile((char*)sensorFilename.c_str(), defaultProcessId, (char*)sensorFilename.c_str());
    this->fileSystem->close((char*)sensorFilename.c_str(), defaultProcessId);
    std::ostringstream output;
    output << "Sensor data file closed and saved to file '" << sensorFilename << "'.";
    this->appendToLogTimeHour(output.str());
}

std::string DataNode::returnSensorFile(std::string username) {
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

bool DataNode::handleDatagram(int client_socket, char *datagram, size_t datagram_size) {
    int message_type;
    int node_type; // tipo de nodo emisor
    char response[3000];
    size_t sizeResponse = 0; 
    bool invalidRequest = false;
    bool result = true;
    bool send_response = true;

    if (datagram_size >= 2) {
        message_type = (int)datagram[0];
        node_type = (int)datagram[1];
        // respondemos según el tipo de mensaje
        switch (message_type) {
          case kLogRequestID:
            if (node_type != kIntermediary || datagram_size != sizeof(LogRequestIN)) {
              invalidRequest = true;
            } else {
              LogRequestIN *request = reinterpret_cast<LogRequestIN*>(datagram);
              // construimos el datagrama del header
              std::string log = this->returnLog(request->request_by);
              LongFileHeader header;
              header.message_type = kLongFileHeader;
              header.char_length = log.length();
              if (!log.empty()) {
                header.successful = true;
              } else {
                header.successful = false;
              }
              if (send(client_socket, reinterpret_cast<char *>(&header), sizeof(LongFileHeader), 0) > 0) {
                if (send(client_socket, log.c_str(), log.size(), 0) < 0) {
                  std::cerr << "Error sending response to client." << std::endl;
                  result = false;
                } else {
                  send_response = false;
                }
              } else {
                std::cerr << "Error sending response to client." << std::endl;
                result = false;
              }
            }
            default:
              // se considera el mensaje como invalido.
              invalidRequest = true;
              break;
        }
    } else {
        // el datagrama es invalido
        invalidRequest = true;
    }

    // La solicitud recibida es invalida
    if (invalidRequest) {
        InvalidRequest invalid;
        invalid.message_type = kInvalidRequest;
        invalid.source_node = kUserHandler;
        sizeResponse = sizeof(InvalidRequest);
        strncpy(response, reinterpret_cast<char*>(&invalid), sizeResponse);
    }
    if(send_response) {
      if (send(client_socket, response, sizeResponse, 0) < 0) {
      std::cerr << "Error sending response to client." << std::endl;
      return false;
    }
    }
    std::cout << "\tResponse sent to client." << std::endl;
    return result;
}

