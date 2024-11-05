#include "ClientNode.hpp"
#include "networkConfig.hpp"
#include "utilities.hpp"


// constructor
ClientNode::ClientNode(std::string logFilename, int processId) 
: Client(logFilename, processId) {}

// destructor
ClientNode::~ClientNode() {}

// Método que devuelve el un string con el significado de ciertos
// datagramas frecuentes que representan errores
std::string ClientNode::getErrorString(int type) {
  std::string response;
  switch (type) {
    case kInvalidRequest:
      response = "The request arrived to a node that cannot handle it.";
      break;
    case kCommunicationError:
      response = "Intermediary node cannot communicate successfully with a secondary node.";
      break;
    case kUnknownError:
      response = "Unknown error.";
    default:
      // se considera el mensaje como invalido.
      response = "Received an invalid message from intermediary node.";
      break;
  }
  std:cout << response << std::endl;
  return response;
}

bool ClientNode::authenticateUser(const std::string &username
, const std::string &password, std::vector<std::string> &response) {
  // buffer donde se recibe la respuesta;
  char buffer[kMaxDatagramSize];
  memset(buffer, 0, kMaxDatagramSize);
  // convertimos el password a hash
  std::string hash = generateHASH_SHA256(password);
  // construimos el datagrama
  AuthenticationRequest login_data;
  login_data.message_type = kAuthenticationRequestCI;
  login_data.source_node = kApplication;
  strncpy(login_data.username, username.c_str(), 32);
  strncpy(login_data.hash, hash.c_str(), 64);
  login_data.username[32] = '\0';
  login_data.hash[64] = '\0';

  // enviamos el mensaje al intermediario y recibimos la respuesta
  bool result = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&login_data)
  , sizeof(login_data), buffer, kMaxDatagramSize, 5);

  if(result) {
    // limpiar el vector
    response.clear();
    int message_type = (int)buffer[0];
    if (message_type == kAuthenticationSuccessIC) {
      AuthenticationSuccessIC* confirmation;
      confirmation = reinterpret_cast<AuthenticationSuccessIC*>(buffer);
      // Agregamos al vector, en orden, el nombre, apellido y permisos. 
      response.push_back(confirmation->name);
      response.push_back(confirmation->last_name);
      response.push_back(std::to_string(confirmation->permissions));
      // TODO: mover a bitacora
      std::cout << "User " + std::string(confirmation->name) + " " + 
                            std::string(confirmation->last_name) + 
                            " has successfully logged in with permissions <" + 
                            std::to_string(confirmation->permissions) + ">.\n";
    } else if (message_type == kAuthenticationFailure) {
        AuthenticationFailure* failure;
        failure = reinterpret_cast<AuthenticationFailure*>(buffer);
      std::cout << "Invalid username and/or password. Error message: " <<
        failure->error << std::endl;
      response.push_back(failure->error);
      result = false;
    } else {
      response.push_back(this->getErrorString((MessageType)message_type));
      result = false;
    }
  // Imprimimos según la respuesta recibida
  }

  return result;
}

// 
bool ClientNode::addUser(const std::string &added_by_user, const std::string &username
, const std::string &password, const uint8_t permissions,  int8_t floors[32]
, const std::string &name, const std::string &lastName, std::string& response) {
  // buffer donde se recibe la respuesta;
  char buffer[kMaxDatagramSize];
  memset(buffer, 0, kMaxDatagramSize);
  // construimos el datagrama
  AddUserRequestCI user_Info;
  // blanqueamos el datagrama
  memset(&user_Info, 0, sizeof(user_Info)); 
  user_Info.source_node = kApplication;
  user_Info.message_type = kAddUserRequestCI;
  // Copiamos los datos de entrada en la estructura
  string hash = generateHASH_SHA256(password);
  strncpy(user_Info.hash, hash.c_str(), sizeof(user_Info.hash) - 1);
  strncpy(user_Info.addedByUser, added_by_user.c_str(), sizeof(user_Info.addedByUser) - 1);
  strncpy(user_Info.username, username.c_str(), sizeof(user_Info.username) - 1);
  user_Info.permissions = permissions;
  std::memcpy(user_Info.floors, floors, sizeof(user_Info.floors));
  strncpy(user_Info.name, name.c_str(), sizeof(user_Info.name) - 1);
  strncpy(user_Info.last_name, lastName.c_str(), sizeof(user_Info.last_name) - 1);
  user_Info.user_identification = 1; // TODO: resolver esto
  
  // enviamos el mensaje al intermediario y recibimos la respuesta
  bool result = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&user_Info)
  , sizeof(user_Info), buffer, kMaxDatagramSize, 15);

  if(result) {
    response.clear();
    int message_type = (int)buffer[0];
    if (message_type == kUserChangesConfirmation) {
      UserChangesConfirmation* confirmation;
      confirmation = reinterpret_cast<UserChangesConfirmation*>(buffer);
      if(confirmation->successful) {
        response = "User " + username + " added successfully.";
      } else {
        response = "Error: Failed to add user " + username + ".";
        result = false;
      }
      std::cout << response << std::endl;
    } else {
      response = this->getErrorString(message_type);
      result = false;
    }
  }
  return result;
}

// Si un argumento se envía vacío, el nodo de usuario mantiene el valor anterior. 
bool ClientNode::modifyUser(const std::string &modify_by_user, const std::string current_username
, const std::string &username, const std::string &password, const uint8_t permissions
, int8_t floors[32], const std::string &name, const std::string &last_name
, std::string &response) {
  // buffer donde se recibe la respuesta;
  char buffer[kMaxDatagramSize];
  memset(buffer, 0, kMaxDatagramSize);

  // construimos el datagrama
  ModifyUserRequestCI user_Info;
  // blanqueamos el datagrama
  memset(&user_Info, 0, sizeof(ModifyUserRequestCI)); 
  user_Info.source_node = kApplication;
  user_Info.message_type = kModifyUserRequestCI;
  // Copiamos los datos de entrada en la estructura
  string hash;
  if(!password.empty()){
    hash = generateHASH_SHA256(password);
  }
  strncpy(user_Info.new_hash, hash.c_str(), sizeof(user_Info.new_hash) - 1);
  strncpy(user_Info.modify_by, modify_by_user.c_str(), sizeof(user_Info.modify_by) - 1);
  strncpy(user_Info.current_username, current_username.c_str(), sizeof(user_Info.current_username) - 1);
  strncpy(user_Info.new_username, username.c_str(), sizeof(user_Info.new_username) - 1);
  user_Info.new_permissions = permissions;
  std::memcpy(user_Info.new_floors, floors, sizeof(user_Info.new_floors));
  strncpy(user_Info.new_name, name.c_str(), sizeof(user_Info.new_name) - 1);
  strncpy(user_Info.new_last_name, last_name.c_str(), sizeof(user_Info.new_last_name) - 1);
  user_Info.user_identification = 1; // TODO: resolver esto
  // enviamos el mensaje al intermediario y recibimos la respuesta
  bool result = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&user_Info)
  , sizeof(ModifyUserRequestCI), buffer, kMaxDatagramSize, 15);

  if(result) {
    response.clear();
    int message_type = (int)buffer[0];
    if (message_type == kUserChangesConfirmation) {
      UserChangesConfirmation* confirmation;
      confirmation = reinterpret_cast<UserChangesConfirmation*>(buffer);
      if(confirmation->successful) {
        response = "User " + username + " modified successfully.";
      } else {
        response = "Error: Failed to modify user " + username + ".";
        result = false;
      }
      std::cout << response << std::endl;
    } else {
      response = this->getErrorString(message_type);
      result = false;
    }
  }
  return result;
}
