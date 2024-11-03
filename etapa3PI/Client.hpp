#ifndef CLIENT_HPP
#define CLIENT

#include "Log.hpp"
class Client : public Log {
protected:
  // Método que se usa para conectarse a otro nodo, devuelve el socket.
  int connectToNode(const std::string& ip, int port);
  // cerrar la conexión
  bool closeConnection(int client_socket);
  // Método que se usa para enviar un datagrama después de establecer una conexión
  bool sendDatagram(int client_socket, char* datagram
  , size_t datagram_size);
  // Método que se utiliza para obtener una respuesta. Incluye un `timeout`.
  bool receiveDatagramWithTimeout(int client_socket, char* response_buffer
  , size_t buffer_size, int timeout_sec);
  // Método que se utiliza para manejar los datagramas y tomar una decisión
  // con base en el mensaje recibido. Notar que se puede sobreescribir. 
  virtual bool handleDatagram(int client_socket, char* datagram
  , size_t datagram_size);
public:
  Client(std::string logFilename, int processId);
  ~Client();
};

#endif