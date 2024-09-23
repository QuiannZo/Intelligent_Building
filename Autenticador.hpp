#include <iostream>
#include <cstring>

#include "FAT.hpp"

#ifndef AUTENTICADOR_HPP
#define AUTENTICADOR_HPP

class Autenticador {
private:
   FAT* data;

public:
    Autenticador(/* args */);
    ~Autenticador();
    // Methods
    bool autenticar(char *username, char * hash);
    FAT* getData() { return data; }
};
#endif