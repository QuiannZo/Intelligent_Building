#ifndef NODE
#define NODE

#include "socketList.hpp"
#include <string>

class Node {
private:
    // Atributos
    int port;
    int server_socket;
    // Métodos
    bool handleConnection(int client_socket);
    int connectToNode(const std::string& ip, int port);
    bool sendDatagram(const std::string& ip, int port
    , const char* datagram, size_t datagram_size);
public:
    // constructor y destructor
    Node(int port);
    ~Node();
    // Métodos
    // Inicializar la configuración del servidor. 
    bool initServer(); 
    // Método que se utiliza para que el servidor empiece a correr,
    // siempre debe ser previamente inicializado.
    void run();
};
#endif