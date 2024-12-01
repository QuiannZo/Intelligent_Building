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
  bool send_response = true;
  bool invalidRequest = false;
  bool connection_error= false;
  bool result = true;
  std::string log;

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
                  connection_error = true;
              }
              // Cerrar el socket
              this->closeConnection(client_socket);
            }
          }
        }
        break; 
      case kAddUserRequestCI:
        if (node_type != kApplication || datagram_size != sizeof(AddUserRequestCI)) {
          invalidRequest = true;
        } else {
          datagram[0] = kAddUserRequestIU;
          datagram[1] = kIntermediary;
          // Reenviar al nodo de usuarios
          if(this->connectSendReceive(kUserHandlerIPv4, kUserHandlerPort, datagram
          , datagram_size - 2, response, kMaxDatagramSize, 10)) {
            if (!response[0] == kUserChangesConfirmation) {
              response[0] = kUnknownError;
            }
          } else {
            connection_error = true;
          }
        }    
        break;
      case kModifyUserRequestCI:
        if (node_type != kApplication || datagram_size != sizeof(ModifyUserRequestCI)) {
          invalidRequest = true;
        } else {
          datagram[0] = kModifyUserRequestIU;
          datagram[1] = kIntermediary;
          // Reenviar al nodo de usuarios
          if(this->connectSendReceive(kUserHandlerIPv4, kUserHandlerPort, datagram
          , sizeof(ModifyUserRequestIU), response, kMaxDatagramSize, 10)) {
            if (!response[0] == kUserChangesConfirmation) {
              response[0] = kUnknownError;
            }
          } else {
            connection_error = true;
          }
        }
        break;
      case kUserListRequestCI:
        // Solicitud debe venir de intermediario
        if (node_type != kApplication || datagram_size != sizeof(UserListRequestCI)) {
            invalidRequest = true;
        } else {
            datagram[0] = kUserListRequestIU;
            datagram[1] = kIntermediary;
            datagram_size = sizeof(UserListRequestIU);
            // La función `connectResendLongString` se encargará del reenvío
            if (this->connectResendLongString(client_socket, datagram, datagram_size, 
                                              response, sizeof(LongFileHeader), 
                                              kIntermediary, kUserHandlerIPv4, kUserHandlerPort, 5)) {
                send_response = false;
            } else {
                connection_error = true;
            }
        }
        break;
      case kUserInfoRequestCI:
        if (node_type != kApplication || datagram_size != sizeof(UserInfoRequestCI)) {
            invalidRequest = true;
        } else {
            // Cambiar tipo de mensaje y el nodo de origen
            datagram[0] = kUserInfoRequestIU;
            datagram[1] = kIntermediary;
            // Establecer conexión con el `UserHandler`
            if (this->connectSendReceive(kUserHandlerIPv4, kUserHandlerPort, datagram,
                                        sizeof(UserInfoRequestIU), response, kMaxDatagramSize, 15)) {
                // Verificamos si el mensaje es del tipo `kUserInfoResponseUI`
                if (response[0] == kUserInfoResponseUI) {
                  response[0] = kUserInfoResponseIC;
                  sizeResponse = sizeof(UserInfoResponse);
                } else {
                   response[0] = kUnknownError;
                }
            } else {
                connection_error = true;
            }
        }
        break;
      case kLogRequestCI:
        // Solicitud debe venir de intermediario
        if (node_type != kApplication || datagram_size != sizeof(LogRequestCI)) {
          invalidRequest = true;
        } else {
          datagram[1] = kIntermediary;
          datagram_size = sizeof(LogRequestIN);
          LogRequestCI* request = reinterpret_cast<LogRequestCI*>(datagram);
          bool result = false;
          if (request->node_required == kUserHandler) {
            datagram[0] = kLogRequestIU;
            result = this->connectResendLongString(client_socket, datagram, datagram_size, 
                                            response, sizeof(LongFileHeader), 
                                            kIntermediary, kUserHandlerIPv4, kUserHandlerPort, 5);
          } else if (request->node_required == KDataCollector) {
            datagram[0] = kLogRequestID;
            result = this->connectResendLongString(client_socket, datagram, datagram_size, 
                                            response, sizeof(LongFileHeader), 
                                            kIntermediary, kDataNodeIPv4, kDataNodePort, 5);
          } else if (request->node_required == kIntermediary) {
            // caso en que se solicita la bitácora del nodo intermediario
            LogRequestIN *request = reinterpret_cast<LogRequestIN*>(datagram);
            // construimos el datagrama del header
            log = this->returnLog(request->request_by);
            LongFileHeader header;
            header.message_type = kLongFileHeader;
            header.source_node = kIntermediary;
            header.char_length = log.length();
            if (!log.empty()) {
              header.successful = true;
            } else {
              header.successful = false;
            }
            if (send(client_socket, reinterpret_cast<char *>(&header), sizeof(LongFileHeader), 0) > 0) {
              if (send(client_socket, log.c_str(), log.size(), 0) < 0) {
                std::cerr << "Error sending response to client." << std::endl;
              } else {
                result = true;
              }
            } else {
              std::cerr << "Error sending response to client." << std::endl;
            }
          } else {
            invalidRequest = true;
          }
          if (result) {
            send_response = false;
          } else {
            connection_error = true;
          }
        }
        break;
      case kSensorInfoRequestCI:
        if (node_type != kApplication || datagram_size != sizeof(SensorInfoRequestCI)) {
          invalidRequest = true;
        } else {
          bool result;
          datagram[0] = kSensorInfoRequestID;
          datagram[1] = kIntermediary;
          datagram_size = sizeof(SensorInfoRequestID);
          result = this->connectResendLongString(client_socket, datagram, datagram_size, 
                                            response, sizeof(LongFileHeader), 
                                            kIntermediary, kDataNodeIPv4, kDataNodePort, 5);
          if (result) {
            send_response = false;
          } else {
            connection_error = true;
          }
        }
        break;
      case kLogRequestBL:
        // construimos el datagrama del header
        log = this->returnLog("Backup_node");
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
        if (result) {
          send_response = false;
        } else {
          connection_error = true;
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
    std::cerr << "\tError: invalid request received." << std::endl;
  } else if (connection_error) {
      CommunicationError error;
      error.message_type = kCommunicationError;
      error.error_node = kUserHandler;
      sizeResponse = sizeof(CommunicationError);
      memcpy(response, reinterpret_cast<char*>(&error), sizeResponse);
  }
  // Responder
  if (send_response) {
    response[1] = kIntermediary; // cambiar origen
    if (send(client_socket, response, sizeResponse, 0) < 0) {
      std::cerr << "Error sending response to client." << std::endl;
      return false;
    }
  std::cout << "\tResponse send to client." << std::endl;
  }
  return true;
}

bool Intermediary::resendLongString(int source_socket, int dest_socket
, int total_size, int timeout_sec) {
  if (source_socket < 0 || dest_socket < 0) {
    return false;
  }

  size_t bytes_received = 0;
  const size_t chunk_size = 256;
  char buffer[chunk_size];
  size_t remaining;
  size_t current_chunk_size;

  while (bytes_received < total_size) {
    memset(buffer, 0, chunk_size);
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

  std::cout << "\tData forwarded to destination node." << std::endl;
  return true;
}

bool Intermediary::connectResendLongString(int client_socket, char *datagram, size_t datagram_size, 
                                           char *response, size_t response_size, 
                                           uint8_t intermediary_type, const std::string ip, int port, size_t timeout) {
  // Conectar con el nodo de usuario usando los parámetros de IP y puerto
  int user_node_socket = this->connectToNode(ip, port);
  if (user_node_socket < 0) {
    std::cerr << "Error connecting to user handler node at " << ip << ":" << port << std::endl;
    return false;
  }
  // Enviar el datagrama al nodo de usuario
  if (this->sendDatagram(user_node_socket, datagram, datagram_size)) {
    // Esperar respuesta
    if (this->receiveDatagramWithTimeout(user_node_socket, response, response_size, timeout)) {
      // Verificar si es un mensaje de tipo `kLongFileHeader`
      if (response[0] == kLongFileHeader) {
        response[1] = intermediary_type;  // Cambiar el origen a "intermediario"
        // Reenviar la respuesta al cliente
        if (send(client_socket, response, response_size, 0) < 0) {
          std::cerr << "Error sending response to client." << std::endl;
          this->closeConnection(user_node_socket);
          return false;
        }
        // Procesar el reenvío de una cadena larga
        LongFileHeader* header = reinterpret_cast<LongFileHeader*>(response);
        if (!this->resendLongString(user_node_socket, client_socket, header->char_length, timeout)) {
          std::cerr << "Error during long string resend." << std::endl;
          this->closeConnection(user_node_socket);
          return false;
        }
        this->closeConnection(user_node_socket);
        return true;
      } else {
        std::cerr << "Unexpected response type received." << std::endl;
      }
    } else {
      std::cerr << "Timeout receiving datagram response." << std::endl;
    }
  } else {
    std::cerr << "Error sending datagram to user node socket." << std::endl;
  }
  // Cerrar la conexión en caso de error
  this->closeConnection(user_node_socket);
  return false;
}
