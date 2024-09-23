#include "Autenticador.hpp"

Autenticador::Autenticador(/* args */){ 
    this->data = new FAT();
}

Autenticador::~Autenticador() { }

bool Autenticador::autenticar(char *username, char * hash) {
    return this->data->searchCredentials(username, hash);
}