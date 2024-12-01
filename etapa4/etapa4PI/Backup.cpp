#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <chrono>

#include "Backup.hpp"

// Constructor
Backup::Backup(std::string logFilename, int processId, int port) 
: Node(logFilename, processId, port) {
  // apenas se inicia, se hace un backup 
  this->requestSaveFiles();
  // iniciar el hilo secundario
  backupThread = std::thread(&Backup::backupTask, this);
}

Backup::~Backup() {
  // detener y esperar el hilo secundario
  running = false;
  if (backupThread.joinable()) {
    backupThread.join();
  }
  // cuando se cierra, también se hace backup
  this->requestSaveFiles();
}

bool Backup::handleDatagram(int client_socket, char *datagram, size_t datagram_size) {
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
          case kLogRequestIB:
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
          case KBackupState:
            if (node_type != kIntermediary || datagram_size != sizeof(BackupState)) {
              invalidRequest = true;
            } else { 
              BackupState *request = reinterpret_cast<BackupState*>(datagram);

              std::string state = "Last backups made:\nUser node log: " + this->updateLogUser +
                "\nData node log: " + this->updateLogDataNode + "\nIntermediary node log: " +
                this->updateLogIntermediary + "\nSensors database: " + this->updateUserInfo +
                "\nUsers database: " + this->updateUserInfo + "\n";
              LongFileHeader header;
              // construimos el datagrama del header
              header.message_type = kLongFileHeader;
              header.char_length = state.length();
              if (send(client_socket, reinterpret_cast<char *>(&header), sizeof(LongFileHeader), 0) > 0) {
                if (send(client_socket, state.c_str(), state.size(), 0) < 0) {
                  std::cerr << "Error sending response to client." << std::endl;
                  result = false;
                } else {
                  send_response = false;
                  this->appendToLogTimeHour(std::string("Status of backups returned to the user ").append(request->request_by));
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


/*
Metodo que se comunica cada de uno de los sensores y GUARDE
reciba el string y que si lo recibe bien lo guarde.
*/
void Backup::requestSaveFiles() {
  // obtener hora en que se comienza el proceso de copia de seguridad
  string time = this->getCurrentDateTime();
  //time.append(".txt");
  // crear datagram
  LogRequestBL request;
  request.message_type = kLogRequestBL;
  request.source_node = kBackupServer;
  DataRequestBD requestData;
  requestData.message_type = kDataRequestBD;
  requestData.source_node = kBackupServer;
  
  string buffer;
  // Pedir datos a nodo de usuarios 
  // Bitácora
  this->connectSendReceiveLong(kUserHandlerIPv4, kUserHandlerPort,
    reinterpret_cast<char*>(&request), sizeof(LogRequestBL), buffer, 5, 5);
  std::string file_name = "log_user_node";
  saveFile(file_name.append("_").append(time).append(".txt"), buffer);
  this->appendToLogTimeHour("The security copy of 'log_user_node' was made.");
  updateLogUser = time;
  // Pedir datos de usuarios
  buffer.clear();
  this->connectSendReceiveLong(kUserHandlerIPv4, kUserHandlerPort,
    reinterpret_cast<char*>(&requestData), sizeof(DataRequestBD), buffer, 5, 5);
  file_name = "users_data";
  saveFile(file_name.append("_").append(time).append(".txt"), buffer);
  this->appendToLogTimeHour("The security copy of 'log_user_node' was made.");
  updateSensorsInfo = time;
  
  // Pedir datos a nodo de datos
  // Bitácora
  string buffer2;
  this->connectSendReceiveLong(kDataNodeIPv4, kDataNodePort,
    reinterpret_cast<char*>(&request), sizeof(LogRequestBL), buffer2, 5, 5);
  file_name = "log_data_node";
  saveFile(file_name.append("_").append(time).append(".txt"), buffer2);
  this->appendToLogTimeHour("The security copy of 'log_data_node' was made.");
  updateLogDataNode = time;
  // Pedir datos de sensores
  buffer2.clear();
  this->connectSendReceiveLong(kDataNodeIPv4, kDataNodePort,
    reinterpret_cast<char*>(&requestData), sizeof(DataRequestBD), buffer2, 5, 5);
  file_name = "sensors_data";
  saveFile(file_name.append("_").append(time).append(".txt"), buffer2);
  this->appendToLogTimeHour("The security copy of 'log_user_node' was made.");
  updateUserInfo = time;

  //  Pedir datos a nodo intermediario 
  // Bitácora
  string buffer3;
  this->connectSendReceiveLong(kIntermediaryIPv4, kIntermediaryPort,
  reinterpret_cast<char*>(&request), sizeof(LogRequestBL), buffer3, 5, 5);
  file_name = "log_intermediary_node";
  saveFile(file_name.append("_").append(time).append(".txt"), buffer3);
  updateLogIntermediary = time;
  this->appendToLogTimeHour("The security copy of 'log_intermediary_node' was made.");
  std::cout << "The files were backed up." << std::endl;
}

 void Backup::saveFile(string filename, string data) {
  // modificamos el nombre del archivo para que no de problemas
  std::string newFilename = filename; std::replace(newFilename.begin(), newFilename.end(), '/', '-'); 
  std::replace(newFilename.begin(), newFilename.end(), ':', '-');

  // Abrir un archivo con extensión .txt en modo de escritura
  std::ofstream outFile(newFilename);
  if (outFile.is_open()) {
      outFile << data;
      outFile.close();
  } else {
      std::cerr << "Error: could not open file." << std::endl;
  }

 }


void Backup::backupTask() {
  // revisar cada minuto que no se haya detenido el programa
  while (running) {
    std::this_thread::sleep_for(std::chrono::minutes(1)); // Espera 1 minuto
    if (++minutesPassed == 30) {
      //solicitar los archivos y realizar la copia de seguridad
      this->requestSaveFiles();
      minutesPassed = 0; 
    }
    if (!running) {
      break;
    }
  }
}
