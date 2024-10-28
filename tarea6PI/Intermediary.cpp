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
Intermediary::Intermediary(int port) : Node(port) {
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
    message_type = (int)datagram[0];
    node_type = (int)datagram[1];
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
                  confirmation->user_identification = 1;
                }
              } else {
                CommunicationError error;
                error.message_type = kCommunicationError;
                error.error_node = kUserHandler;
                sizeResponse = sizeof(CommunicationError);
                memcpy(response, reinterpret_cast<char*>(&error), sizeResponse);
              }
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