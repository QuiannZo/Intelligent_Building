#include <iostream>
#include <string>
#include "FAT.hpp"

#ifndef USUARIO_HPP
#define USUARIO_HPP

class Usuario {
private:
    std::string userName;
    std::string userPassword;
    std::string userPasswordHash;

public:
    void addUser(std::string pUserName, std::string pPassword, std::string pPermission, std::string pName, std::string pLastname, std::string pId, char* filename, FAT* myFat);
    void print(bool verbose = false);
    std::string hash(std::string password);
};

#endif