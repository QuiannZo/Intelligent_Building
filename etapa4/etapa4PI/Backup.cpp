#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "Backup.hpp"

// Constructor
Backup::Backup(std::string logFilename, int processId, int port) 
: Node(logFilename, processId, port) {
 
}

Backup::~Backup() {

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

void Backup::run() {
  // Estructura que contiene la dirección del cliente
  struct sockaddr_storage ip_remote;
  socklen_t l = sizeof(ip_remote);
  // Se usa para almacenar la dirección IP del cliente
  char str_ip_remote[INET6_ADDRSTRLEN];
  // Socket del cliente
  int client_socket = -1;
  while (true) {
    // Aceptar la conexión
    client_socket = accept(server_socket, (struct sockaddr*)&ip_remote, &l);
    if (client_socket < 0) {
        sleep(1); // aqui es donde se debe hacer la confirmacion
        continue;
    }
    struct sockaddr_in *s = (struct sockaddr_in*)&ip_remote;
    inet_ntop(AF_INET, &s->sin_addr, str_ip_remote, sizeof str_ip_remote);
    std::ostringstream ss5;
    ss5 << "Connection from Remote IP: " << str_ip_remote;
    std::string message_remote_connected = ss5.str();
    this->appendToLogTimeHour(message_remote_connected);
    std::cout << message_remote_connected << std::endl;
    if (!handleConnection(client_socket)) {
        std::ostringstream ss6;
        ss6 << "Error handling the connection with the client ";
        std::string message_error_connection = ss6.str();
        this->appendToLogTimeHour(message_error_connection);
        std::cout << message_error_connection << std::endl;
    }
    // Cerrar el socket
    std::ostringstream ss7;
    ss7 << "Connection closed: " << str_ip_remote;
    std::string message_connection_closed = ss7.str();
    this->appendToLogTimeHour(message_connection_closed);
    std::cout << message_connection_closed << std::endl;
    std::cout << message_connection_closed << std::endl;
    close(client_socket);
  }

}