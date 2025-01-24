#ifndef INTERMEDIARY_HPP
#define INTERMEDIARY_HPP

#include "Node.hpp"
class Intermediary : public Node {
private:
  bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size) override;
  // Método que se encarga de reenviar un mensaje largo
  bool resendLongString(int source_socket, int dest_socket, int total_size, int timeout_sec);
  // Método que se encarga de realizar la conexión y reenvían un archivo largo
  bool connectResendLongString(int client_socket, char *datagram, size_t datagram_size, 
                               char *response, size_t response_size, 
                               uint8_t intermediary_type, const std::string ip, int port, size_t timeout);


public:
  Intermediary(std::string logFilename, int processId, int port);
  ~Intermediary();

};


#endif