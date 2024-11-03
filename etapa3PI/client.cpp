
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>
#include <iomanip>
#include <openssl/sha.h>
#include <cstring>

#include "utilities.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

// TODO: extraer de la clase Nodo todo el código relacionada a clientes, esto
// para crear una clase Cliente.
int main(){
  // ESTABLECER CONEXIÓN
  int result = 0;
  const std::string server_ip = kIntermediaryIPv4;
  const int server_port = kIntermediaryPort;
  // `AF_INET`: especifica que sea un IPv4
  // `SOCK_STREAM`: especifica que se usa un socket de tipo TCP
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
      std::cerr 
        << "Error creating the socket to connect to another node" 
        << std::endl;
      return 1;
    }
  // estructura que almacena la dirección del nodo destino 
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(server_port);
  // convertir la IP al binario 
  if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0) {
    std::cerr << "Invalid IP address: " << server_ip << std::endl;
    close(client_socket);
    return 2;
  }
  // Conectar con el nodo servidor
  if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to node at " << server_ip << ":" << server_port << std::endl;
    close(client_socket);
    return 3;
  }
  // Se estableció la conexión 
  std::cout << "Connected to node at " << server_ip << ":" << server_port << std::endl;

  // CREAR MENSAJE:
  // Pedir usuario y contraseña:
  char username[32];
  char password[64];
  cout << "Enter Username" << endl;
  cin.getline(username, sizeof(username));
  cout << "Enter password" << endl;
  cin.getline(password, sizeof(password));
  // Obtenemos el hash
  const std::string password_str(password);
  std::string hash = generateHASH_SHA256(password_str);
  // Inicializar el datagrama
  AuthenticationRequest login_data;
  login_data.message_type = kAuthenticationRequestCI;
  login_data.source_node = kApplication;
  strncpy(login_data.username, username, 32);
  strncpy(login_data.hash, hash.c_str(), 64);
  login_data.username[32] = '\0';
  login_data.hash[64] = '\0';

  // ENVIAR MENSAJE:
  // No se envió correctamente el mensaje
  if (send(client_socket, reinterpret_cast<char*>(&login_data)
  , sizeof(login_data), 0) < 0) {
    std::cerr << "Error sending datagram to node at " 
      << server_ip << ":" << server_port << std::endl;
    close(client_socket);
    return false;
  }
  // Se envió correctamente el mensaje
  std::cout << "Datagram sent to " << server_ip << ":" 
    << server_port << std::endl;
  
  // LEER RESPUESTA DEL SERVIDOR
  char response_buffer[kMaxDatagramSize];
  memset(response_buffer, 0, sizeof(response_buffer));
  // Leer la respuesta del servidor
  ssize_t bytes_received = recv(client_socket
  , response_buffer, sizeof(response_buffer), 0);
  if (bytes_received < 0) {
    std::cerr << "Error reading response from node at " << server_ip << ":" << server_port << std::endl;
    close(client_socket);
    return 4;
  }
  // Mostrar la respuesta recibida
  int message_type = (int)response_buffer[0];
  // Imprimimos según la respuesta recibida
  switch (message_type) {
    case kAuthenticationSuccessIC:
      // Convertimos el char* al `struct` correspondiente
      AuthenticationSuccessIC* confirmation;
      confirmation = reinterpret_cast<AuthenticationSuccessIC*>(response_buffer);
      std::cout << "User verified. \n" << "\t Name: " 
      << confirmation->name << " | Last name: " << confirmation->last_name << std::endl;
      // imprimir los permisos de los usuarios
      checkPermissions(confirmation->permissions);
      break; 
    case kAuthenticationFailure:
      AuthenticationFailure* failure;
      failure = reinterpret_cast<AuthenticationFailure*>(response_buffer);
      std::cout << "Invalid username and/or password. Error message: " <<
        failure->error << std::endl;
      break;
    case kInvalidRequest:
      std::cout << "Server node cannot handle the request." << std::endl;
      break;
    case kCommunicationError:
      std::cout << "Server node cannot communicate successfully with a secondary node." << std::endl;
      break;
    default:
      // se considera el mensaje como invalido.
      std::cout << "Received an invalid message." << std::endl;
      break;
  }


  // Cerrar el socket
  close(client_socket);

  return result;
}