#ifndef NODE
#define NODE

#include <string>
#include "socketList.hpp"
#include "Client.hpp"

class Node : public Client {
protected:
    // Atributos
    int port;
    int server_socket;
    // Métodos
    bool handleConnection(int client_socket);
public:
    // constructor y destructor
    Node(std::string logFilename, int processId, int port);
    ~Node();
    // Métodos
    // Inicializar la configuración del servidor. 
    bool initServer(); 
    // Método que se utiliza para que el servidor empiece a correr,
    // siempre debe ser previamente inicializado.
    void run();
};
#endif