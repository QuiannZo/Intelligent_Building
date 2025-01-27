#include "ClientNode.hpp"
#include "networkConfig.hpp"
#include "utilities.hpp"


// constructor
ClientNode::ClientNode(std::string logFilename, int processId) 
: Client(logFilename, processId) {}

// destructor
ClientNode::~ClientNode() {}

uint16_t ClientNode::getUserID() {
    return this->user_id;
}

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
      break;
    case kTransmissionError:
      response = "An error occurs during transmission.";
      break;
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
      this->user_id = 1; // TODO:
      this->username = username;
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
        response = "Error: Failed to modify user '" + current_username + "'. Error message: "
        + confirmation->error + "\n";
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

bool ClientNode::getUserList(std::string request_by, std::vector<std::string> &response) {
  // buffer donde se recibe la respuesta;
  // construimos el datagrama
  UserListRequestCI request;
  request.message_type = kUserListRequestCI;
  request.source_node = kApplication;
  strncpy(request.request_by, request_by.c_str(), sizeof(request.request_by) - 1);
  request.user_identification = 1; // TODO:
  string buffer;
  bool result = true;
  if(this->connectSendReceiveLong(kIntermediaryIPv4, kIntermediaryPort
  , reinterpret_cast<char*>(&request), sizeof(UserListRequestCI), buffer, 5, 5)) {
    response.clear();
    std::stringstream ss(buffer);
    std::string token;
    // separar por comas
    while (std::getline(ss, token, ',')) {
      response.push_back(token);
    }
  } else {
    response.push_back(getErrorString((uint8_t)buffer.c_str()[0]));
    result = false;
  } 
  // TODO:borrar
  std::cout << "Buffer[delete message]: " << buffer << std::endl;
  return result;
}

bool ClientNode::getUserInformation(const std::string request_by, const std::string &username
                                    , std::vector<std::string> &response) {
  // buffer donde se recibe la respuesta;
  char buffer[kMaxDatagramSize];
  memset(buffer, 0, kMaxDatagramSize);

  // construimos el datagrama
  UserInfoRequestCI user_info;
  // blanqueamos el datagrama
  memset(&user_info, 0, sizeof(UserInfoRequestCI)); 
  strncpy(user_info.username, username.c_str(), sizeof(user_info.username) - 1);
  user_info.source_node = kApplication;
  user_info.message_type = kUserInfoRequestCI;
  user_info.user_identification = 1; // TODO
  strncpy(user_info.request_by, request_by.c_str(), sizeof(user_info.request_by) - 1);

  bool result = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&user_info)
  , sizeof(UserInfoRequestCI), buffer, kMaxDatagramSize, 15);
  response.clear();
  if(result) {
    int message_type = (int)buffer[0];
    if (message_type == kUserInfoResponseIC) {
      UserInfoResponse* info_response;
      info_response = reinterpret_cast<UserInfoResponse*>(buffer);
      if(info_response->successful) {
        std::cout << "[delete message] Username: " 
          << info_response->username 
          << ", Name: " << info_response->name 
          << ", Last Name: " << info_response->last_name 
          << ", Permissions: <" 
          << static_cast<int>(info_response->permissions) 
          << ">\n";
          // almacenamos los datos en el vector
          response.push_back(info_response->username);
          response.push_back(info_response->name);
          response.push_back(info_response->last_name);
          response.push_back(std::to_string(info_response->permissions));
          if (info_response->is_active) {
            response.push_back("Active");
          } else {
            response.push_back("Inactive");
          }
          return true;
      } else {
        std::cout << "\tError: " << info_response->error << std::endl;
      }
    } else {
      response.push_back(this->getErrorString(message_type));
    }
  }
  return false;
}

bool ClientNode::getNodeLog(std::string request_by, std::string &response, uint8_t node_type) {
  // construimos el datagrama
  LogRequestCI request;
  memset(&request, 0, sizeof(LogRequestCI));
  request.message_type = kLogRequestCI;
  request.node_required = static_cast<NodeType>(node_type);
  request.source_node = kApplication;
  strncpy(request.request_by, request_by.c_str(), sizeof(request.request_by) - 1);
  request.user_identification = 1; // TODO
  bool result = true;
  response.clear();
  if(!this->connectSendReceiveLong(kIntermediaryIPv4, kIntermediaryPort
  , reinterpret_cast<char*>(&request), sizeof(LogRequestCI), response, 5, 5)) {
    response = this->getErrorString((uint8_t)response.c_str()[0]);
    result = false; 
  }
  // TODO:borrar
  std::cout << "Buffer[delete message]: " << response << std::endl;
  return result;
}

bool ClientNode::getSensorData(std::string request_by, std::string &response) {
  // construimos el datagrama
  SensorInfoRequestCI request;
  memset(&request, 0, sizeof(SensorInfoRequestCI));
  request.message_type = kSensorInfoRequestCI;
  request.source_node = kApplication;
  strncpy(request.request_by, request_by.c_str(), sizeof(request.request_by) - 1);
  request.user_identification = 1; // TODO
  bool result = true;
  response.clear();
  if(!this->connectSendReceiveLong(kIntermediaryIPv4, kIntermediaryPort
  , reinterpret_cast<char*>(&request), sizeof(SensorInfoRequestCI), response, 5, 5)) {
    response = this->getErrorString((uint8_t)response.c_str()[0]);
    result = false; 
  }
  // TODO:borrar
  std::cout << "Buffer[delete message]: " << response << std::endl;
  return result;
}

bool ClientNode::activeDeactivateUser(const std::string &modify_by_user, const std::string username, bool status, std::string& response) {
  // buffer donde se recibe la respuesta;
  char buffer[kMaxDatagramSize];
  memset(buffer, 0, kMaxDatagramSize);

  // construimos el datagrama
  ActivateDeactivateUserRequest user_Info;
  // blanqueamos el datagrama
  memset(&user_Info, 0, sizeof(ActivateDeactivateUserRequest)); 
  user_Info.source_node = kApplication;
  user_Info.message_type = kActivateDeactivateUserRequest;
  // Copiamos los datos de entrada en la estructura
  strncpy(user_Info.modify_by, modify_by_user.c_str(), sizeof(user_Info.modify_by) - 1);
  strncpy(user_Info.username, username.c_str(), sizeof(user_Info.username) - 1);
  user_Info.status = status;
  // enviamos el mensaje al intermediario y recibimos la respuesta
  bool result = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&user_Info)
  , sizeof(ActivateDeactivateUserRequest), buffer, kMaxDatagramSize, 15);

  if(result) {
    response.clear();
    int message_type = (int)buffer[0];
    if (message_type == kUserChangesConfirmation) {
      UserChangesConfirmation* confirmation;
      confirmation = reinterpret_cast<UserChangesConfirmation*>(buffer);
      if(confirmation->successful) {
        response = "User " + username + " modified successfully.";
      } else {
        response = "Error: Failed to modify user '" + username + "'. Error message: "
        + confirmation->error + "\n";
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

bool ClientNode::getBackupState(std::string request_by, std::string &response) {
  // construimos el datagrama
  BackupState request;
  memset(&request, 0, sizeof(BackupState));
  request.message_type = KBackupState;
  request.source_node = kApplication;
  strncpy(request.request_by, request_by.c_str(), sizeof(request.request_by) - 1);
  bool result = true;
  response.clear();
  if (!this->connectSendReceiveLong(kIntermediaryIPv4, kIntermediaryPort, reinterpret_cast<char *>(&request), sizeof(BackupState), response, 5, 5))
  {
      response = this->getErrorString((uint8_t)response.c_str()[0]);
      result = false;
  }
  // TODO:borrar
  std::cout << "Buffer[delete message]: " << response << std::endl;
  return result;
}

std::string ClientNode::checkPermissions(uint8_t user_permissions) {
    std::vector<std::string> result;

    if (user_permissions & 1) {
        result.push_back("User Administrator");
    }
    if (user_permissions & 2) {
        result.push_back("Database Administrator");
    }
    if (user_permissions & 4) {
        result.push_back("Floor Manager");
    }
    if (user_permissions & 8) {
        result.push_back("Building Manager");
    }
    if (user_permissions & 16) {
        result.push_back("System Administrator");
    }
    if (user_permissions & 32) {
        result.push_back("Auditor");
    }

    result.push_back("No permissions assigned.");

    return result[0];
}

std::string ClientNode::getSystemState() {
  string result = "Distributed system status:\nIntermediary Node: ";
  NodeState request;
  request.message_type = kNodeState;
  request.source_node = kApplication;
  char buffer[10];
  // consultarle a todos los nodos si están activos:
  // enviamos el mensaje al intermediario y recibimos la respuesta
  // Intermediario
  bool connection = this->connectSendReceive(kIntermediaryIPv4
  , kIntermediaryPort, reinterpret_cast<char*>(&request)
  , sizeof(NodeState), buffer, 10, 5);
  if (connection) {result.append("ON\n");} else {result.append("OFF\n");}
  // Node de datos 
  result.append("Data node: ");
  connection = this->connectSendReceive(kDataNodeIPv4
  , kDataNodePort, reinterpret_cast<char*>(&request)
  , sizeof(NodeState), buffer, 10, 5);
  if (connection) {result.append("ON\n");} else {result.append("OFF\n");}
  // Nodo de usuarios
  result.append("User node: ");
  connection = this->connectSendReceive(kUserHandlerIPv4
  , kUserHandlerPort, reinterpret_cast<char*>(&request)
  , sizeof(NodeState), buffer, 10, 5);
  if (connection) {result.append("ON\n");} else {result.append("OFF\n");}
  // Nodo de copia de seguridad
  result.append("Backup node: ");
  connection = this->connectSendReceive(kBackupNodeIPv4
  , kBackupPort, reinterpret_cast<char*>(&request)
  , sizeof(NodeState), buffer, 10, 5);
  if (connection) {result.append("ON\n");} else {result.append("OFF\n");}

  std::cout << "Buffer[delete message]:\n" << result << std::endl;
  return result;
}
