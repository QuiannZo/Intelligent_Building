#ifndef INTERMEDIARY_HPP
#define INTERMEDIARY_HPP

#include "Node.hpp"
class Intermediary : public Node {
private:
  bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size) override;
  // Método que se encarga de reenviar un mensaje largo
  bool resendLongString(int source_socket, int dest_socket, size_t total_size, int timeout_sec);

public:
  Intermediary(std::string logFilename, int processId, int port);
  ~Intermediary();

};


#endif