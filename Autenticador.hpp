#include <iostream>
#include <cstring>

#ifndef AUTENTICADOR_HPP
#define AUTENTICADOR_HPP

class Autenticador {
private:
   

public:
    Autenticador(/* args */);
    ~Autenticador();
    // Methods
    bool autenticar(char *username, char * hash);
};
#endif