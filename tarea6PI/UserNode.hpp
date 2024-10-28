#ifndef USER_NODE_HPP
#define USER_NODE_HPP

#include "Node.hpp"
#include "../UserHandler.hpp"
class UserNode : public Node {
private:
  // Atributos
  UserHandler* userHandler;
  // Métodos
  bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size) override;

public:
  UserNode(int port);
  ~UserNode();

};


#endif