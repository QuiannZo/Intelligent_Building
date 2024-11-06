#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Node.hpp"
#include "socketList.hpp"

// Constructor
Node::Node(std::string logFilename, int processId, int port) 
: Client(logFilename, processId), port(port), server_socket(0) {
}

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
    // Cerrar el socket
    std::cout << "Connection closed: " << str_ip_remote << std::endl;
    std::cout << std::endl;
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
  // Llamamos a la función que maneja el datagrama y da el mensaje
  return this->handleDatagram(client_socket, received_message, bytes_read);
}
