#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

#include <vector>

#include "Log.hpp"
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

class UserHandler : public Log {
private:
    std::string usersFilename;
    HashHandler* hashHandler;
    std::vector<std::string> splitString(const char* input);
public:
    UserHandler(std::string logFilename, int processId, std::string usersFilename);
    ~UserHandler();
    bool addUser(const std::string &addedByUser, const std::string& username, const std::string& hash, const uint8_t permissions
                , const std::string& floors, const std::string& name, const std::string& lastName
                ,const std::string& userId);
    bool authenticateUser(const std::string& username, const std::string& hash, std::string &error);
    //TODO: hay que diseñar algún sistema que únicamente devuelva información cuando el usuario tiene "sesión iniciada"
     bool hasPermissions(const std::string& username, permissions role);
    std::string generateHash(const std::string& password);
    std::vector<std::string> getUserInformation(const std::string& username);
    bool modifyUserEntry(std::string currentUserEntry, std::string newUserEntry);
    std::string vectorToString(const std::vector<std::string>& vec);
};

#endif