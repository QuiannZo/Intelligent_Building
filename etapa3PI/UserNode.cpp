#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "UserNode.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

// Constructor
UserNode::UserNode(std::string logFilename, int processId, std::string usersFilename, int port) 
: Node(logFilename, processId, port), usersFilename(usersFilename) {
 this->hashHandler = new HashHandler();
  //TODO: está sección presenta código repetido con el CollectionHandler, considerar mover esto a la clase base "log".
  bool fileCreated = false;
  bool error = false;
  // Try opening the file in read mode to check if it exists
  std::ifstream fileCheck(usersFilename.c_str());
  if (fileCheck) {
      std::cout << "File '" <<  usersFilename << "' already exists, it will be loaded into the file system." << std::endl;
      fileCheck.close();
  } else {
      // Create the file if it doesn't exist
      std::ofstream file(usersFilename);
      if (file) {
          std::cout << "File created: " << usersFilename << std::endl;
          file.close();
          fileCreated = true;
      } else {
          std::cerr << "Error creating file: " << usersFilename << std::endl;
          error = true;
      }
  }
  // load file into our filesystem 
  if (!error) {
      std::ostringstream output;
      if (this->fileSystem->loadFile((char*)usersFilename.c_str(), processId)) {
          if (fileCreated) {
              output << "File '" << usersFilename << "' <Type:File-user-data> created and loaded into filesystem.";
          } else {
              output << "File '" << usersFilename << "' <Type:File-user-data> loaded into filesystem.";
          }   
          if(!this->fileSystem->open((char*)usersFilename.c_str(), defaultProcessId)) {
              std::cerr << "Error <filesystem>: could not open file '" <<  usersFilename << "'.\n";
          } else {
              if (fileCreated) {
                  if (!this->fileSystem->append((char*)usersFilename.c_str(), this->getProcessId() 
                      ,(char*)"username,hash,permissions,[floors],name,lastName,userId,createdDate,lastUpdateDate,isActive\n")) {
                          std::cerr << "Error: could not append to '" << usersFilename << "'."  << std::endl;
                      }
              }
          }
          if (!this->appendToLogTimeHour(output.str())) {
              std::cerr << "Error: could not append to '" << usersFilename << "'."  << std::endl;
          }
      } else {
          std::cerr << "Error: could not open file " << usersFilename << std::endl;
      }
  }
}

// Destructor
UserNode::~UserNode() {
  // TODO: se debe manejar la excepción que sucede cuando control + c
  // save log before destroy object 
  this->fileSystem->saveFile((char*)usersFilename.c_str(), defaultProcessId, (char*)usersFilename.c_str());
  this->fileSystem->close((char*)usersFilename.c_str(), defaultProcessId);
  std::ostringstream output;
  output << "Users data file closed and saved to file '" << usersFilename << "'.";
  this->appendToLogTimeHour(output.str());

  delete this->hashHandler;
}

std::string UserNode::floorsToString(int8_t floors[32]) {
  int i = 0;
  bool first = true;
  std::string result;
  while (i < 32) {
    if(floors[i] != 0){
      if (first) {
        result = result + std::to_string(floors[i]);
        first = false;
      } else {
        result = result + "&" +std::to_string(floors[i]);
      }
    } else {
      break;
    }
    i++;
  }
  return result;
}

bool UserNode::handleDatagram(int client_socket, char *datagram, size_t datagram_size) {
    int message_type;
    int node_type; // tipo de nodo emisor
    char response[kMaxDatagramSize];
    size_t sizeResponse = kMaxDatagramSize;
    bool invalidRequest = false;
    bool send_response = true;
    bool result = true;
    if (datagram_size >= 2)
    {
        message_type = (int)datagram[0];
        node_type = (int)datagram[1];
        // respondemos según el tipo de mensaje
        switch (message_type)
        {
        case kAuthenticationRequestIU:
            // Solicitud debe venir de intermediario
            if (node_type != kIntermediary || datagram_size != sizeof(AuthenticationRequest)) {
                invalidRequest = true;
            }
            else
            {
                // Convertimos el datagrama al respectivo `struct`.
                AuthenticationRequest *request = reinterpret_cast<AuthenticationRequest *>(datagram);
                std::string error;
                if (this->authenticateUser(std::string(request->username), std::string(request->hash), error))
                {
                    // Obtenemos un vector con la información del usuario
                    std::vector<std::string> userInformation = this->getUserInformation(std::string(request->username));
                    AuthenticationSuccessUI authInfo;
                    authInfo.message_type = kAuthenticationSuccessUI;
                    authInfo.source_node = kUserHandler;
                    authInfo.permissions = static_cast<uint8_t>(std::stoi(userInformation[2]));
                    strncpy(authInfo.name, userInformation[4].c_str(), 33);
                    strncpy(authInfo.last_name, userInformation[5].c_str(), 33);
                    // guardamos la respuesta
                    memcpy(response, reinterpret_cast<char *>(&authInfo), sizeResponse);
                }
                else
                {
                    AuthenticationFailure errorInfo;
                    errorInfo.message_type = kAuthenticationFailure;
                    errorInfo.source_node = kUserHandler;
                    strncpy(errorInfo.error, error.c_str(), 64);
                    // guardamos la respuesta
                    memcpy(response, reinterpret_cast<char *>(&errorInfo), sizeResponse);
                }
            }
            break;
        case kModifyUserRequestIU:
            if (node_type != kIntermediary || datagram_size != sizeof(ModifyUserRequestIU)) {
              invalidRequest = true;
            } else {
                ModifyUserRequestIU *request = reinterpret_cast<ModifyUserRequestIU *>(datagram);
                std::string error;
                bool result = this->modifyUser(request->modify_by, request->current_username
                , request->new_username, request->new_hash, request->new_permissions
                , this->floorsToString(request->new_floors), request->new_name
                , request->new_last_name, "102", error);
                UserChangesConfirmation confirmation;
                confirmation.message_type = kUserChangesConfirmation;
                confirmation.source_node = kUserHandler;
                confirmation.successful = result;
                if(!result) {
                  strncpy(confirmation.error, error.c_str(), sizeof(confirmation.error));
                }
                // guardamos la respuesta
                sizeResponse = sizeof(UserChangesConfirmation);
                memcpy(response, reinterpret_cast<char *>(&confirmation), sizeResponse);
            }
          break;
        case kAddUserRequestIU:
            if (node_type != kIntermediary || datagram_size != sizeof(AddUserRequestIU)) {
                invalidRequest = true;
            }
            else {
                // Convertimos el datagrama al respectivo `struct`.
                AddUserRequestIU *request = reinterpret_cast<AddUserRequestIU *>(datagram);
                bool result = this->addUser(request->addedByUser, request->username
                , request->hash, request->permissions, this->floorsToString(request->floors)
                , request->name, request->last_name, "101");
                // Construimos el mensaje de confirmación 
                UserChangesConfirmation confirmation;
                confirmation.message_type = kUserChangesConfirmation;
                confirmation.source_node = kUserHandler;
                confirmation.successful = result;
                // guardamos la respuesta
                sizeResponse = sizeof(UserChangesConfirmation);
                memcpy(response, reinterpret_cast<char *>(&confirmation), sizeResponse);
            }
            break;
        case kUserListRequestIU:
          if (node_type != kIntermediary || datagram_size != sizeof(UserListRequestIU)) {
            invalidRequest = true;
          } else {
            // construimos el datagrama del header
            std::vector<std::string> users = this->getUserList();
            std::string users_str = this->vectorToString(users);
            LongFileHeader header;
            header.message_type = kLongFileHeader;
            header.char_length = users_str.length();
            if (!users_str.empty()) {
              header.successful = true;
            } else {
               header.successful = false;
            }
            if (send(client_socket, reinterpret_cast<char *>(&header), sizeof(LongFileHeader), 0) > 0) {
              if (send(client_socket, users_str.c_str(), users_str.size(), 0) < 0) {
                std::cerr << "Error sending response to client." << std::endl;
                result = false;
              } else {
                send_response = false;
              }
            } else {
              std::cerr << "Error sending response to client." << std::endl;
              result = false;
            }
          }
          break;
        case kUserInfoRequestIU:
          if (node_type != kIntermediary || datagram_size != sizeof(UserInfoRequestIU)) {
              invalidRequest = true;
          } else {
            // Convertimos el datagrama al respectivo `struct`.
                UserInfoRequestIU *request = reinterpret_cast<UserInfoRequestIU *>(datagram);
                // TODO: agregar algo a la bitacora, porque getUserInformation no lo hace.
                std::vector<std::string> userInformation = this->getUserInformation(request->username);
                // Construimos el mensaje de respuesta 
                UserInfoResponse user_info;
                user_info.message_type = kUserInfoResponseUI;
                user_info.source_node = kUserHandler;
                if(userInformation.empty()) {
                  user_info.successful = false;
                  strcpy(user_info.error, "User not found.");
                  this->appendToLogTimeHour("[User information]: '" + std::string(request->request_by) 
                          + "' attempted to get information of user '" + std::string(request->username)
                          + "', but the user does not exist.");
                } else {
                  this->appendToLogTimeHour("[User information]: '" + std::string(request->request_by) 
                                            + "' got information of user '" + std::string(request->username)
                                            + "'.");
                  user_info.successful = true;
                  user_info.permissions = static_cast<uint8_t>(std::stoi(userInformation[2]));
                  strncpy(user_info.username, userInformation[0].c_str(), 33);
                  strncpy(user_info.name, userInformation[4].c_str(), 33);
                  strncpy(user_info.last_name, userInformation[5].c_str(), 33);
                  if (userInformation[9] == "1") {
                    user_info.is_active = true;
                  } else {
                    user_info.is_active = false;
                  }
                }
                // guardamos la respuesta
                sizeResponse = sizeof(UserInfoResponse);
                memcpy(response, reinterpret_cast<char *>(&user_info), sizeResponse);
          }
          break; 
        case kLogRequestIU:
          if (node_type != kIntermediary || datagram_size != sizeof(LogRequestIN)) {
            invalidRequest = true;
          } else {
            LogRequestIN *request = reinterpret_cast<LogRequestIN*>(datagram);
            // construimos el datagrama del header
            std::string log = this->returnLog(request->request_by);
            LongFileHeader header;
            header.message_type = kLongFileHeader;
            header.char_length = log.length();
            if (!log.empty()) {
              header.successful = true;
            } else {
              header.successful = false;
            }
            if (send(client_socket, reinterpret_cast<char *>(&header), sizeof(LongFileHeader), 0) > 0) {
              if (send(client_socket, log.c_str(), log.size(), 0) < 0) {
                std::cerr << "Error sending response to client." << std::endl;
                result = false;
              } else {
                send_response = false;
              }
            } else {
              std::cerr << "Error sending response to client." << std::endl;
              result = false;
            }
          }
        default:
          // se considera el mensaje como invalido.
          invalidRequest = true;
          break;
        }
    } else {
    // el datagrama es invalido
    invalidRequest = true;
  }
  // La solicitud recibida es invalida
  if(invalidRequest) {
    InvalidRequest invalid;
    invalid.message_type = kInvalidRequest;
    invalid.source_node = kUserHandler;
    sizeResponse = sizeof(InvalidRequest);
    strncpy(response, reinterpret_cast<char*>(&invalid), sizeResponse);
    std::cerr << "\tError: invalid request received." << std::endl;
  }
  if (send_response) {
    if (send(client_socket, response, sizeResponse, 0) < 0) {
      std::cerr << "Error sending response to client." << std::endl;
      result = false;
    }
    std::cout << "\tResponse send to client." << std::endl;
  }
  return result;
}

std::vector<std::string> UserNode::splitString(const char* input) {
  std::vector<std::string> result;
  std::stringstream ss(input);
  std::string token;
  // separate string by commas
  while (std::getline(ss, token, ',')) {
    result.push_back(token);
  }
  return result;
}

std::string UserNode::vectorToString(const std::vector<std::string> &vec) {
  std::stringstream result;
  for (size_t i = 0; i < vec.size(); ++i) {
    result << vec[i];
    if (i != vec.size() - 1) {
        result << ",";  // separate by comma
    } //else {
        //result << "\n";  // add \n at the end
    //}
  }
  return result.str();
}

std::vector<std::string> UserNode::getUserList() {
  std::vector<std::string> userVector;
  std::vector<std::string> userEntry;
  if (this->fileSystem->resetFileCursors((char *)this->usersFilename.c_str())) {
    this->appendToLogTimeHour("[User information]: attempting get user list.");
    char buffer[1024] = {};
    // ignore first line
    this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool stop = false;
    while (!stop) {
        if(result) {
          userEntry = this->splitString(buffer);
          if (userEntry.size() != 10) {
            stop = true;
          } else {
            userVector.push_back(userEntry[0]);
            result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                        , buffer, 1000, this->defaultProcessId);
          } 
        } else {
          stop == true;
        }
    }
    this->appendToLogTimeHour("[User information]: user list returned.");
  }
  return userVector;
}

bool UserNode::modifyUser(const std::string &modify_by_user
, const std::string &current_username, const std::string &username
, const std::string &hash, const uint8_t permissions, const std::string &floors
, const std::string &name, const std::string &lastName, const std::string &userId
, std::string &error) {
  // Obtenemos la hora
  std::string dateTime = this->getCurrentDateTime();
  // Obtener la información del usuario
  std::vector<std::string> user_info = this->getUserInformation(current_username);
  if (user_info.size() != 10) {
    this->appendToLogTimeHour(
    "Modify user [failed]: '" + modify_by_user + "'  tried to modify '" +
    username + "', but the user was not found in the registry.");
    error = "User not found.";
    return false;
  }
  // Guardamos una copia de la entrada
  std::string user_copy = this->vectorToString(user_info); 
  // revisar los valores que se deben modificar
  if (!username.empty()) {
    user_info[0] = username;
  }
  if(!hash.empty()) {
    user_info[1] = hash;
  }
  if(permissions != 0){
    user_info[2] = std::to_string(permissions);
  }
  if(!floors.empty()){
    user_info[3] = "[" + floors +"]";
  }
  if(!name.empty()){
    user_info[4] = name;
  }
  if(!lastName.empty()){
    user_info[5] = lastName;
  }
  // TODO: por el momento el userId no se modifica porque
  // no se está usando.
  // actualizamos la fecha de actualización 
  user_info[8] = dateTime;
  // obtenemos el string del usuario modificado
  std::string user_mod = this->vectorToString(user_info);
  if (this->modifyUserEntry(user_copy, user_mod)) {
    this->appendToLogTimeHour(
      "Modify user: '" + modify_by_user + "'   modified '" +
      username + "'.");
    return true;
  }
  this->appendToLogTimeHour(
    "Modify user [failed]: '" + modify_by_user + "'  tried to modify '" +
    username + "', but the user registry could not be modified.");
  error = "Failed to modify user record.";
  return false;
}

bool UserNode::addUser(const std::string &addedByUser, const std::string &username, const std::string &hash, const uint8_t permissions
, const std::string& floors, const std::string &name, const std::string &lastName, const std::string &userId) {
  // TODO: EVITAR que se puedan agregar dos usuarios con el mismo nombre.
  std::string dateTime = this->getCurrentDateTime();
  //"username,hash,permissions,[floors],name,lastName,userId,createdDate,lastUpdateDate,isActive"
  std::string concatenated = username + "," + hash + "," + std::to_string(permissions) + ",[" 
                              + floors + "],"
                              + name + "," + lastName + "," + userId + ","
                              + dateTime + "," + dateTime // created and updated
                              + ",1\n"; //  the `1` is used to indicate that the user is active 
  if(concatenated.empty()) {
    return false;
  }
  // add the new user to the filesystem 
  bool result = this->fileSystem->append((char*)usersFilename.c_str(), this->getProcessId(), (char*)concatenated.c_str());
  if (result) {
    this->appendToLogTimeHour(
        "New user: '" + addedByUser + "' added [Username: " + username 
                    + " | Name: " + name + " " + lastName
                    + " | Permissions: " + std::to_string(permissions) + "].");
  } else {
    this->appendToLogTimeHour(
        "New user [failed] [probably error related to append() of the file system]: '" 
                    + addedByUser + "' tried to add [Username: " + username 
                    + " | Name: " + name + " " + lastName
                    + " | Permissions: " + std::to_string(permissions) + "].");
  }
  return result;
}

bool UserNode::authenticateUser(const std::string &username, const std::string &hash, std::string &error) {
  if (this->fileSystem->resetFileCursors((char*)this->usersFilename.c_str())) {
    this->appendToLogTimeHour("[Log-in]: attempting to authenticate '" + username + "'.");
    char buffer[1024] = {};
    // ignore first line
    this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool stop = !result;
    bool userFound = false;
    bool hashValidated = false;
    while (!stop) {
      if(result) {
        std::vector<std::string> stringVector = this->splitString(buffer);
        if (stringVector.size() != 10) {
          stop = true;
        } else {
          if (stringVector[0] == username) {
            userFound = true;
            if (stringVector[1] == hash) {
                hashValidated = true;
            }
            stop = true;
          } else {
            result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                    , buffer, 1000, this->defaultProcessId);
          }
        } 
      } else {
          stop = true;
      }  
    }
    if (hashValidated) {
        this->appendToLogTimeHour("[Log-in]: user '" + username + "' validated.");
    } else {
        if (userFound) {
            this->appendToLogTimeHour("[Log-in]: invalid hash for user '" + username + "'.");
            error = "Invalid password";
        } else {
            this->appendToLogTimeHour("[Log-in]: user '" + username + "' not found.");
            error = "Invalid username";
        }
    }
    return hashValidated;
  }
  return false;
}

std::string UserNode::generateHash(const std::string &password) {
  return this->hashHandler->generateHASH_SHA256(password);
}

bool UserNode::hasPermissions(const std::string &username, permissions role) {
  std::vector<std::string> user = getUserInformation(username);
  if (user.size() == 10) {
    uint8_t userPermission = static_cast<uint8_t>(std::stoi(user[2]));
    if ((userPermission & role) == role) {
      return true;
    }
  }
  return false;
}

std::vector<std::string> UserNode::getUserInformation(const std::string &username) {
  std::vector<std::string> stringVector;
  if (this->fileSystem->resetFileCursors((char *)this->usersFilename.c_str())) {
    this->appendToLogTimeHour("[Log-in]: attempting get information of user '" + username + "'.");
    char buffer[1024] = {};
    // ignore first line
    this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                            , buffer, 1000, this->defaultProcessId);
    bool stop = false;
    bool userFound = false;
    while (!stop) {
      if(result) {
        stringVector = this->splitString(buffer);
        if (stringVector.size() != 10) {
          stop = true;
        } else {
            if (stringVector[0] == username) {
              userFound = true;
              stop = true;
            } else {
              result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                      , buffer, 1000, this->defaultProcessId);
            }
          } 
      } else {
        stop == true;
      }
    }
    if (userFound) {
      this->appendToLogTimeHour("[User information]: information of user '" + username + "' returned.");
    } else {
      this->appendToLogTimeHour("[User information]: user '" + username + "' not found.");
    }
  }
  return stringVector;
}

bool UserNode::modifyUserEntry(std::string currentUserEntry, std::string newUserEntry) {
  std::string usersData;
  if (this->fileSystem->getCompleteFile((char*)this->usersFilename.c_str(), this->defaultProcessId, usersData)) {
    size_t pos = usersData.find(currentUserEntry);
    if (pos != std::string::npos) {
    // replace 
        usersData.replace(pos, currentUserEntry.length(), newUserEntry);
    }
    // rewrite the file system
    return this->fileSystem->write((char*)this->usersFilename.c_str(), this->defaultProcessId, (char*)usersData.c_str());
  }
  return false;
}

