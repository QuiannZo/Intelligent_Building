#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Intermediary.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

// Constructor
Intermediary::Intermediary(std::string logFilename, int processId, int port) 
: Node(logFilename, processId, port) {
}

// Destructor
Intermediary::~Intermediary() {
}

bool Intermediary::handleDatagram(int client_socket, char *datagram
, size_t datagram_size) {
  int message_type;
  int node_type; // tipo de nodo emisor
  char response[kMaxDatagramSize];
  size_t sizeResponse = kMaxDatagramSize;
  bool invalidRequest = false;

  if (datagram_size >= 2) {
    message_type = (uint8_t)datagram[0];
    node_type = (uint8_t)datagram[1];

    // respondemos según el tipo de mensaje
    switch (message_type) {
      case kAuthenticationRequestCI:
        // Solicitud debe venir de intermediario
        if (node_type != kApplication || datagram_size != sizeof(AuthenticationRequest)) {
          invalidRequest = true;
        } else {
          // establecemos una conexión con el `UserHandler`:
          int client_socket = this->connectToNode(kUserHandlerIPv4, kUserHandlerPort);
          if (client_socket > 0) {
            // cambiamos el tipo de mensaje y el nodo nodo de origen
            datagram[0] = kAuthenticationRequestIU;
            datagram[1] = kIntermediary;
            // Enviamos el datagrama
            if (this->sendDatagram(client_socket, datagram, datagram_size)) {
              // Como máximo esperamos 15s
              if (this->receiveDatagramWithTimeout(client_socket, response, kMaxDatagramSize, 15)) {
                // Verificamos si es un mensaje de tipo `kAuthenticationSuccessUI`
                if(response[0] == kAuthenticationSuccessUI) {
                  AuthenticationSuccessIC* confirmation = reinterpret_cast<AuthenticationSuccessIC*>(response);
                  confirmation->message_type = kAuthenticationSuccessIC;
                  // TODO: trabajar en la tabla interna que se usa para llevar registro de
                  // los usuarios con sesión iniciada.
                  //confirmation->user_identification = 1;
                }
              } else {
                CommunicationError error;
                error.message_type = kCommunicationError;
                error.error_node = kUserHandler;
                sizeResponse = sizeof(CommunicationError);
                memcpy(response, reinterpret_cast<char*>(&error), sizeResponse);
              }
              // Cerrar el socket
              this->closeConnection(client_socket);
            }
          }
        }
        break; 
      case kLogRequestCI:
        // Solicitud debe venir de intermediario
        if (node_type != kApplication || datagram_size != sizeof(LogRequestCI)) {
          invalidRequest = true;
        } else {
          // Establecemos una conexión con el `DataNode`
          int client_socket = this->connectToNode(kDataNodeIPv4, kDataNodePort);
          if (client_socket > 0) {
            // Cambiamos el tipo de mensaje y el nodo de origen
            LogRequestID datagram2;
            datagram2.message_type = kLogRequestID;
            datagram2.source_node = kIntermediary;
            datagram2.client_identification = 20;

            // Enviamos el datagrama
            if (this->sendDatagram(client_socket, reinterpret_cast<char*>(&datagram2), sizeof(datagram2))) {
              // Como máximo esperamos 15s
              if (this->receiveDatagramWithTimeout(client_socket, response, kMaxDatagramSize, 15)) {
              } else {
                CommunicationError error;
                error.message_type = kCommunicationError;
                error.error_node = kUserHandler;
                sizeResponse = sizeof(CommunicationError);
                memcpy(response, reinterpret_cast<char*>(&error), sizeResponse);
              }
              // Cerrar el socket
              this->closeConnection(client_socket);
            }
          }
        }
        break;
      
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
  if(invalidRequest) {
    InvalidRequest invalid;
    invalid.message_type = kInvalidRequest;
    invalid.source_node = kIntermediary;
    sizeResponse = sizeof(InvalidRequest);
    memcpy(response, reinterpret_cast<char*>(&invalid), sizeResponse);
  }
  // Responder
  response[1] = kIntermediary; // cambiar origen
  if (send(client_socket, response, sizeResponse, 0) < 0) {
    std::cerr << "Error sending response to client." << std::endl;
    return false;
  }
  return true;
}

bool Intermediary::resendLongString(int source_socket, int dest_socket
, size_t total_size, int timeout_sec) {
  if (source_socket < 0 || dest_socket < 0) {
    return false;
  }

  size_t bytes_received = 0;
  const size_t chunk_size = 256;
  char buffer[chunk_size];
  size_t remaining;
  size_t current_chunk_size;

  while (bytes_received < total_size) {
    // Configurar `fd_set` para monitorear el socket de origen
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(source_socket, &read_fds);

    // Configurar el timeout para `select`
    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;

    // Esperar hasta que haya datos o se alcance el timeout
    int activity = select(source_socket + 1, &read_fds, nullptr, nullptr, &timeout);
    if (activity < 0) {
        std::cerr << "Error with select()." << std::endl;
        return false;
    } else if (activity == 0) {
        std::cerr << "Timeout reached, no data received from node." << std::endl;
        return false;
    }

    // Leer el fragmento actual desde el socket de origen
    remaining = total_size - bytes_received;
    current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
    
    ssize_t result = recv(source_socket, buffer, current_chunk_size, 0);
    if (result < 0) {
        std::cerr << "Error reading chunk from source node." << std::endl;
        return false;
    } else if (result == 0) {
        std::cerr << "Connection closed by source node before full message was received." << std::endl;
        return false;
    }

    // Enviar el fragmento recibido al socket de destino
    ssize_t sent = send(dest_socket, buffer, result, 0);
    if (sent < 0 || sent != result) {
        std::cerr << "Error sending chunk to destination node." << std::endl;
        return false;
    }
    bytes_received += result;
  }

  std::cout << "Data forwarded to destination node." << std::endl;
  return true;
}
