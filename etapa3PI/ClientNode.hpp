#ifndef CLIENT_NODE_HPP
#define CLIENT_NODE_HPP

#include <vector>
#include "Client.hpp"
#include "socketList.hpp"

class ClientNode : public Client {
private:
    std::string getErrorString(int type);
public:
  ClientNode(std::string logFilename, int processId);
  ~ClientNode();
  // Métodos que se usan para enviar mensajes al intermediario
  // Comunicación hacia el nodo de usuarios
  // Autenticar usuarios
  bool authenticateUser(const std::string& username, const std::string& password
  , std::vector<std::string>& response);
  // Agregar usuario
  bool addUser(const std::string &addedByUser, const std::string& username, const std::string& hash, const uint8_t permissions
          , const std::string& floors, const std::string& name, const std::string& lastName
          ,const std::string& userId);
  // Modificar usuario
  bool modifyUser(const std::string &ModifyByUser, const std::string& username, const std::string& hash, const uint8_t permissions
          , const std::string& floors, const std::string& name, const std::string& lastName
          ,const std::string& userId);
  // Obtener lista de usuarios
  bool getUserList(std::vector<std::string>& response);
  // Obtener información de un usuario en particular
  bool getUserInformation(const std::string& username, std::vector<std::string>& response);
  // Obtener la bitácora del nodo de usuarios
  bool getUserNodeLog(std::string& response);
  
  // Comunicación hacia el nodo de datos
  // Obtener la bitácora del nodo de datos
  bool getDataNodeLog(std::string& response);
  bool getSensorData(std::string& response);
};
#endif