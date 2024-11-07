#ifndef CLIENT_NODE_HPP
#define CLIENT_NODE_HPP

#include <vector>
#include "Client.hpp"
#include "socketList.hpp"

class ClientNode : public Client {
public:
  // atributos que se establecen cuando se realiza el login.
  std::string username;
  std::string name;
  std::string lastName;
  uint16_t user_id = 0;
  uint8_t permissions = 0;
  std::string getErrorString(int type);
public:
  ClientNode(std::string logFilename, int processId);
  ~ClientNode();
  uint16_t getUserID();
  // Métodos que se usan para enviar mensajes al intermediario
  // Comunicación hacia el nodo de usuarios
  // Autenticar usuarios
  bool authenticateUser(const std::string& username, const std::string& password
  , std::vector<std::string>& response);
  // Agregar usuario
  bool addUser(const std::string &added_by_user, const std::string& username, const std::string& password, const uint8_t permissions
          , int8_t floors[32], const std::string& name, const std::string& lastName
          , std::string& response);
  // Modificar usuario
  // Si un argumento se envía vacío, el nodo de usuario mantiene el valor anterior.
  bool modifyUser(const std::string &modify_by_user, const std::string current_username
          , const std::string& username, const std::string& password, const uint8_t permissions
          , int8_t floors[32], const std::string& name, const std::string& last_name
          , std::string& response);
  // Obtener lista de usuarios
  bool getUserList(std::string request_by, std::vector<std::string>& response);
  // Obtener información de un usuario en particular. Devuelve en el vector: nombre de usuario, nombre, apellido, permisos y estado.
  bool getUserInformation(const std::string request_by, const std::string& username, std::vector<std::string>& response);
  // Obtener la bitácora del nodo `node_type`
  bool getNodeLog(std::string request_by, std::string& response, uint8_t node_type);
  
  // Comunicación hacia el nodo de datos
  // Obtener datos de los sensores
  bool getSensorData(std::string request_by, std::string& response);

};
#endif