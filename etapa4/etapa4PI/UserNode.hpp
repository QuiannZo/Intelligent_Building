#ifndef USER_NODE_HPP
#define USER_NODE_HPP

#include "Node.hpp"
#include "HashHandler.hpp"

enum permissions : uint8_t {
    // Next, we show the bits corresponding to each `user type` / permission
    INVALID_PERMISSION = 0,
    USER_ADMINISTRATOR = 1, // bits: 00000001
    DATABASE_ADMINISTRATOR = 2, // bits: 00000010
    FLOOR_MANAGER = 4, // bits: 00000100
    BUILDING_MANAGER = 8, // bits: 00001000
    SYSTEM_ADMINISTRATOR = 16, // bits: 00010000
    AUDITOR = 32 // bits: 00100000
    /**
     * - To build a permission for a user with more than one permission, use the bitwise AND (&) operator. 
     *     Example: USER_ADMINISTRATOR & AUDITOR
     * - To verify that a user has a permission, use bitwise OR (|) operator against the corresponding permission,
     * then compare the result and the permission.
     *     Example: user_info | AUDITOR == AUDITOR
    */ 
};

class UserNode : public Node {
private:
  // Atributos
  std::string usersFilename;
  HashHandler* hashHandler;
  std::string floorsToString(int8_t floors[32]);
  // Métodos
  bool handleDatagram(int client_socket, char* datagram
    , size_t datagram_size) override;
  std::vector<std::string> splitString(const char* input);
  // Métodos que anteriormente pertenecían a la clase `UserHandler`
  bool addUser(const std::string &addedByUser, const std::string& username, const std::string& hash, const uint8_t permissions
              , const std::string& floors, const std::string& name, const std::string& lastName
              ,const std::string& userId);
  bool authenticateUser(const std::string& username, const std::string& hash, std::string &error);
  bool hasPermissions(const std::string& username, permissions role);
  std::string generateHash(const std::string& password);
  std::vector<std::string> getUserInformation(const std::string& username);
  bool modifyUserEntry(std::string currentUserEntry, std::string newUserEntry);
  std::string vectorToString(const std::vector<std::string>& vec);
  std::vector<std::string> getUserList();
  // Método para modificar un usuario
  bool modifyUser(const std::string &modify_by_user, const std::string& current_username
                , const std::string& username, const std::string& hash
                , const uint8_t permissions, const std::string& floors, const std::string& name
                , const std::string& lastName, const std::string& userId, std::string &error);


public:
  UserNode(std::string logFilename, int processId, std::string usersFilename, int port);
  ~UserNode();
};


#endif