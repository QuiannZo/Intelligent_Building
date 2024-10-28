#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "UserNode.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

// Constructor
UserNode::UserNode(int port) : Node(port) {
  this->userHandler = new UserHandler("logUserNode.txt", 1, "usersData.txt");
}

// Destructor
UserNode::~UserNode() {
  // TODO: se debe manejar la excepción que sucede cuando control + c
  delete this->userHandler;
}

bool UserNode::handleDatagram(int client_socket, char *datagram, size_t datagram_size) {
  int message_type;
  int node_type; // tipo de nodo emisor
  char response[kMaxDatagramSize];
  size_t sizeResponse = kMaxDatagramSize;
  bool invalidRequest = false;
  if (datagram_size >= 2) {
    message_type = (int)datagram[0];
    node_type = (int)datagram[1];
    // respondemos según el tipo de mensaje
    switch (message_type) {
      case kAuthenticationRequestIU:
        // Solicitud debe venir de intermediario
        if (node_type != kIntermediary || datagram_size != sizeof(AuthenticationRequest)) {
          invalidRequest = true;
        } else {
          // Convertimos el datagrama al respectivo `struct`.
          AuthenticationRequest* request = reinterpret_cast<AuthenticationRequest*>(datagram);
          std::string error;
          if (this->userHandler->authenticateUser(std::string(request->username)
          , std::string(request->hash), error)) {
            // Obtenemos un vector con la información del usuario
            std::vector<std::string> userInformation = userHandler->getUserInformation(std::string(request->username));
            AuthenticationSuccessUI authInfo;
            authInfo.message_type = kAuthenticationSuccessUI;
            authInfo.source_node = kUserHandler;
            authInfo.permissions = static_cast<uint8_t>(std::stoi(userInformation[2]));
            strncpy(authInfo.name, userInformation[4].c_str(), 33);
            strncpy(authInfo.last_name, userInformation[5].c_str(), 33);
            // guardamos la respuesta
            memcpy(response, reinterpret_cast<char*>(&authInfo), sizeResponse);
          } else {
            AuthenticationFailure errorInfo;
            errorInfo.message_type = kAuthenticationFailure;
            errorInfo.source_node = kUserHandler;
            strncpy(errorInfo.error, error.c_str(), 64);   
            // guardamos la respuesta
            memcpy(response, reinterpret_cast<char*>(&errorInfo), sizeResponse);
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
    invalid.source_node = kUserHandler;
    sizeResponse = sizeof(InvalidRequest);
    strncpy(response, reinterpret_cast<char*>(&invalid), sizeResponse);
  }
      std::cout << "Respuesta: " << response << std::endl;
  if (send(client_socket, response, sizeResponse, 0) < 0) {
    std::cerr << "Error sending response to client." << std::endl;
    return false;
  }
  return true;
}
