#ifndef INTERMEDIARY_HPP
#define INTERMEDIARY_HPP

#include "Node.hpp"
class Intermediary : public Node {
private:
  bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size) override;

public:
  Intermediary(int port);
  ~Intermediary();

};


#endif