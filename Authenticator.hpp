#include <iostream>
#include <cstring>

#include "FAT.hpp"

#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

class Authenticator {
private:
   FAT* data;

public:
    Authenticator(/* args */);
    ~Authenticator();
    // Methods
    bool autenticar(char *username, char * hash);
    FAT* getData() { return data; }
};
#endif