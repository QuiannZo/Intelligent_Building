#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Client.hpp"
#include "socketList.hpp"

// Constructor de la clase
Client::Client(std::string logFilename, int defaultProcessId): Log(logFilename
, defaultProcessId) {
}

// Destructor de la clase
Client::~Client() {
}

// Método utilizado para comunicarse como cliente con otro nodo. Retorna
// el valor correspondiente al socket, o -1 en caso de error.
int Client::connectToNode(const std::string& ip, int port) {
  // En este caso, el cliente es el nodo actual.
  // `AF_INET`: especifica que sea un IPv4
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

// Cierra la conexión del socket especificado.
// Retorna `true` si se cerró exitosamente, `false` en caso contrario.
bool Client::closeConnection(int client_socket) {
  if (client_socket < 0) {
    std::cerr << "Invalid socket. Cannot close connection." << std::endl;
    return false;
  }
  if (close(client_socket) == 0) {
    std::cout << "Connection closed successfully." << std::endl;
    return true;
  } else {
    std::cerr << "Error closing the connection." << std::endl;
    return false;
  }
}

// Método que se utiliza para recibir un mensaje después de establecer una
// conexión con un servidor, incluye un tiempo de espera.
bool Client::receiveDatagramWithTimeout(int client_socket, char *response_buffer
  , size_t buffer_size, int timeout_sec) {
  // Es una estructura que se utiliza para monitorear un descriptor
  // de un archivo (?), en nuestro caso la usamos para monitorear
  // si hay datos en el socket.
  fd_set read_fds;
  // Inicializar la estructura
  FD_ZERO(&read_fds);
  FD_SET(client_socket, &read_fds);
  // Establecer el tiempo de espera
  struct timeval timeout;
  timeout.tv_sec = timeout_sec;
  timeout.tv_usec = 0;
  // Esperar hasta que hayan datos o se haya cumplido el `timeout`
  int activity = select(client_socket + 1, &read_fds, nullptr, nullptr, &timeout);
  if (activity < 0) {
      std::cerr << "Error with select()." << std::endl;
      return false;
  } else if (activity == 0) {
      std::cerr << "Timeout reached, no response received from node." << std::endl;
      return false;
  }
  // Leemos la respuesta
  ssize_t bytes_received = recv(client_socket, response_buffer, buffer_size, 0);
  if (bytes_received < 0) {
      std::cerr << "Error reading response from node." << std::endl;
      return false;
  }
  std::cout << "Response from node: " << response_buffer << std::endl;
  return true;
}

// Método que se utiliza para manejar e interpretar el datagrama. Puede ser
// sobre escrito en las clases que heredan de `Nodo`.
bool Client::handleDatagram(int client_socket, char *datagram
  , size_t datagram_size) {
  // Imprimimos el mensaje completo
  std::cout << "\tMessage received: ";
  for (size_t i = 0; i < datagram_size; ++i) {
    std::cout << datagram[i];
  }
  std::cout << std::endl;
  std::cout << "\tMessage type: " << (int)datagram[0]
    << " | Node type: " << (int)datagram[1];
  std::cout << std::endl;
  // Damos la respuesta que se va a enviar al cliente
  std::string response = "Datagram received successfully.";
  if (send(client_socket, response.c_str(), response.size(), 0) < 0) {
    std::cerr << "Error sending response to client." << std::endl;
    // Solo debe devolver `false` cuando hay un error con la conexión. Si el
    // datagrama recibido es incorrecto, va a enviar un mensaje indicando el
    // error. En ese caso, se considera que se manejo correctamente el
    // datagrama recibido. 
    return false;
  }
  return true;
}

// Enviar un datagrama al nodo servidor. 
bool Client::sendDatagram(int client_socket, char* datagram, size_t datagram_size) {
  // Primero se debe establecer la conexión.
  if (client_socket < 0) {
    return false;
  }
  // No se envió correctamente el mensaje
  if (send(client_socket, datagram, datagram_size, 0) < 0) {
    std::cerr << "Error sending datagram to node." << std::endl;
    close(client_socket);
    return false;
  }
  // Se envió correctamente el mensaje
  std::cout << "Datagram sent to node." << std::endl;
  // Cerrar el socket
  // close(client_socket); <- cerrar el socket siempre afuera
  return true;
}

// Método que realiza el proceso de conectarse, enviar datagrama, 
// recibir respuesta y cerrar conexión. 
bool Client::connectSendReceive(const std::string &ip, int port, char *datagram
, size_t datagram_size, char *response_buffer, size_t buffer_size
, int timeout_sec) {
  // establecemos una conexión
  int client_socket = this->connectToNode(ip, port);
  if (client_socket > 0) {
    // Enviamos el datagrama
    if (this->sendDatagram(client_socket, datagram, datagram_size)) {
      // Obtenemos la respuesta, como máximo esperamos `timeout` s. 
      if (this->receiveDatagramWithTimeout(client_socket, response_buffer
      , buffer_size, timeout_sec)) {
        // Cerrar el socket
        this->closeConnection(client_socket);
        return true;
      }
    }
  }  
  return false;
}

bool Client::sendLongString(int client_socket, const std::string &data) {
  if (client_socket < 0) {
    return false;
  }
  // Obtener el tamaño total del string
  size_t total_size = data.size();
  size_t bytes_sent = 0;
  const size_t chunk_size = 256;
  size_t remaining;
  size_t current_chunk_size;

  while (bytes_sent < total_size) {
    // caracteres restantes
    remaining = total_size - bytes_sent;
    // si es menor a 256, enviar solo esa porción
    current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
    
    // Enviar el fragmento actual
    int result = send(client_socket, data.c_str() + bytes_sent, current_chunk_size, 0);
    if (result < 0) {
        std::cerr << "Error sending chunk to node." << std::endl;
        return false;
    }
    bytes_sent += result;
  }

  std::cout << "\tComplete data sent to node." << std::endl;
  return true;
}

bool Client::receiveLongString(int client_socket, std::string& received_data, size_t total_size, int timeout_sec) {
  if (client_socket < 0) {
    return false;
  }
  received_data.clear();
  // Reservar espacio para el string completo
  received_data.reserve(total_size);  

  size_t bytes_received = 0;
  const size_t chunk_size = 256;
  char buffer[chunk_size];

  while (bytes_received < total_size) {
    // Configurar los `fd_set` para monitorear el socket
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(client_socket, &read_fds);

    // Configurar el tiempo de espera para `select`
    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;

    // Esperar hasta que haya datos o se alcance el timeout
    int activity = select(client_socket + 1, &read_fds, nullptr, nullptr, &timeout);
    if (activity < 0) {
      std::cerr << "Error with select()." << std::endl;
      return false;
    } else if (activity == 0) {
      std::cerr << "Timeout reached, no data received from node." << std::endl;
      return false;
    }

    // Leer el fragmento actual
    size_t remaining = total_size - bytes_received;
    size_t current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
    
    ssize_t result = recv(client_socket, buffer, current_chunk_size, 0);
    if (result < 0) {
      std::cerr << "Error reading chunk from node." << std::endl;
      return false;
    } else if (result == 0) {
      std::cerr << "Connection closed by node before full message was received." << std::endl;
      return false;
    }
    // Agregar el fragmento recibido al string
    received_data.append(buffer, result);
    bytes_received += result;
  }

  std::cout << "Complete data received from node." << std::endl;
  return true;
}

