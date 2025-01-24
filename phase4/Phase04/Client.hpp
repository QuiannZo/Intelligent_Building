#ifndef CLIENT_HPP
#define CLIENT

#include "Log.hpp"
class Client : public Log {
public:
  // Métodos esenciales:
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

  // Métodos para facilitar el intercambio de datagramas:
  // Método que encapsula los métodos `connectToNode`, `sendDatagram`,
  // `receiveDatagramWithTimeout` y `closeConnection`.
  bool connectSendReceive(const std::string& ip, int port,  char* datagram
  , size_t datagram_size, char* response_buffer
  , size_t buffer_size, int timeout_sec);
  // Método que se encarga de enviar un string sin importar el tamaño, 
  // la conexión se debe establecer y cerrar por separado. 
  bool sendLongString(int client_socket, const std::string& data);
  // Método que se encarga de recibir un string largo, se debe conocer el tamaño del mismo. 
  // La conexión se debe establecer y cerrar por separado. 
  bool receiveLongString(int client_socket
  , std::string& received_data, size_t total_size, int timeout_sec);
  // Método que encapsula los métodos `connectToNode`, `sendDatagram`, receiveDatagramWithTimeout,
  // `receiveLongString` y `closeConnection`. Está pensado para recibir archivos grandes.
  bool connectSendReceiveLong(const std::string& ip, int port,  char* datagram
  , size_t datagram_size, std::string& response_buffer
  , int timeout_header_sec, int timeout_chunk_sec);


public:
  Client(std::string logFilename, int processId);
  ~Client();
};

#endif