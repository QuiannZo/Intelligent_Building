#include <iostream>
#include <string>

#ifndef USUARIO_HPP
#define USUARIO_HPP

class Usuario {
private:
    std::string userName;
    std::string userPassword;
    std::string userPasswordHash;

public:
    void addUser(std::string pUserName, std::string pPassword, char* filename);
    void print(bool verbose = false);
    std::string hash(std::string password);
};

#endif