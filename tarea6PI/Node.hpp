#ifndef NODE
#define NODE

#include "socketList.hpp"
#include <string>

class Node {
protected:
    // Atributos
    int port;
    int server_socket;
    // Métodos
    bool handleConnection(int client_socket);
    virtual bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size);
    // método que se usa para conectarse a otro nodo, devuelve el socket.
    int connectToNode(const std::string& ip, int port);
    // método que se usa para enviar un datagrama después de establecer una
    // conexión
    bool sendDatagram(int client_socket, char* datagram
    , size_t datagram_size);
    // método que se utiliza para obtener una respuesta. Incluye un `timeout`.
    bool receiveDatagramWithTimeout(int client_socket, char* response_buffer
    , size_t buffer_size, int timeout_sec);
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