#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Node.hpp"
#include "socketList.hpp"

// Constructor
Node::Node(int port) : port(port), server_socket(0) {}

// Destructor
Node::~Node() {
  if (server_socket > 0) {
    close(server_socket);
  }
}

// Método que se utiliza para inicializar la configuración del servidor. Si
// retorna `false`, no se debe llamar el método `run`.
bool Node::initServer() {
  // `AF_INET`: especifica que se un IPv4
  // `SOCK_STREAM`: especifica que se usa un socket de tipo TCP
  this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket <= 0) {
    std::cerr << "Error creating the server socket" << std::endl;
    return false;
  }
  // En esta estructura se almacena la información de red del nodo
  struct sockaddr_in ip;
  memset(&ip, '0', sizeof(ip));
  ip.sin_family = AF_INET; // IPv4
  // ¿Aceptar mensajes de cualquier dirección IP e interfaz?
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  // Establecer el puerto que vamos a usar
  ip.sin_port = htons(this->port);
  // realizamos la "unión":
  if (bind(this->server_socket, (struct sockaddr*)&ip, sizeof(ip)) < 0) {
    std::cerr << "Error binding the server socket." << std::endl;
    return false;
  }
  // como máximo 25 conexiones en espera
  if (listen(this->server_socket, 25) < 0) {
    std::cerr << "Error setting server to listen." << std::endl;
    return false;
  }
  // servidor inicializado correctamente y escuchando
  std::cout << "[SERVER STARTED ON PORT " << this->port << "]" << std::endl;
  std::cout << "[SERVER LISTENING]" << std::endl;
  return true;
}

// Método con el que el servidor comienza a correr
void Node::run() {
  // Estructura que contiene la dirección del cliente
  struct sockaddr_storage ip_remote;
  socklen_t l = sizeof(ip_remote);
  // Se usa para almacenar la dirección IP del cliente
  char str_ip_remote[INET6_ADDRSTRLEN];
  // Socket del cliente
  int client_socket = -1;
  while (true) {
    // Aceptar la conexión
    client_socket = accept(server_socket, (struct sockaddr*)&ip_remote, &l);
    if (client_socket < 0) {
        sleep(1);
        continue;
    }
    struct sockaddr_in *s = (struct sockaddr_in*)&ip_remote;
    inet_ntop(AF_INET, &s->sin_addr, str_ip_remote, sizeof str_ip_remote);
    std::cout << "Connection from Remote IP: " << str_ip_remote << std::endl;

    if (!handleConnection(client_socket)) {
        std::cerr << "Error handling the connection with the client" << std::endl;
    }
    // cerrar el socket
    close(client_socket);
  }
}

// Método que se encarga de manejar la conexión con el cliente
bool Node::handleConnection(int client_socket) {
    char received_message[kMaxDatagramSize];
    memset(received_message, 0, sizeof(received_message));
    // Leer el mensaje del cliente
    ssize_t bytes_read = read(client_socket, received_message
    , sizeof(received_message) - 1);
    // verificar lectura
    if (bytes_read < 0) {
      std::cerr << "Error reading from client socket." << std::endl;
      return false;
    } else if (bytes_read == 0) {
      std::cerr << "Client disconnected." << std::endl;
      return false;
    }
    received_message[bytes_read] = '\0';
    std::cout << "Command received: " << received_message << std::endl;
    // Dar respuesta
    std::string response = "Processed response.";
    // Verificar error en el envío
    if (send(client_socket, response.c_str(), response.size(), 0) < 0) {
      std::cerr << "Error sending response to client." << std::endl;
      return false; // Return false to indicate failure
    }
    return true; // Successfully processed the connection
}

// Método utilizado para comunicarse como cliente con otro nodo. Retorna
// el valor correspondiente al socket, o -1 en caso de error.
int Node::connectToNode(const std::string& ip, int port) {
  // En este caso, el cliente es el nodo actual.
  // `AF_INET`: especifica que se un IPv4
  // `SOCK_STREAM`: especifica que se usa un socket de tipo TCP
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
      std::cerr 
        << "Error creating the socket to connect to another node" 
        << std::endl;
      return -1;
    }
  // estructura que almacena la dirección del nodo destino 
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  // convertir la IP al binario 
  if (inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr) <= 0) {
    std::cerr << "Invalid IP address: " << ip << std::endl;
    close(client_socket);
    return -1;
  }
  // Conectar con el nodo servidor
  if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to node at " << ip << ":" << port << std::endl;
    close(client_socket);
    return -1;
  }
  // Se estableció la conexión 
  std::cout << "Connected to node at " << ip << ":" << port << std::endl;
  return client_socket;
}

// Enviar un datagrama al nodo servidor. 
bool Node::sendDatagram(const std::string& ip, int port, const char* datagram, size_t datagram_size) {
  // Primero se debe establecer la conexión. 
  int client_socket = connectToNode(ip, port);
  if (client_socket < 0) {
    return false;
  }
  // No se envió correctamente el mensaje
  if (send(client_socket, datagram, datagram_size, 0) < 0) {
    std::cerr << "Error sending datagram to node at " << ip << ":" << port << std::endl;
    close(client_socket);
    return false;
  }
  // Se envió correctamente el mensaje
  std::cout << "Datagram sent to " << ip << ":" << port << std::endl;
  // Cerrar el socket
  close(client_socket);
  return true;
}
