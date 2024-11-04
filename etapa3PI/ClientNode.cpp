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
      response = "Intermediary node cannot handle the request.";
      break;
    case kCommunicationError:
      response = "Intermediary node cannot communicate successfully with a secondary node.";
      break;
    default:
      // se considera el mensaje como invalido.
      response = "Received an invalid message from intermediary node.";
      break;
  }
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
