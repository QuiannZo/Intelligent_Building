#include "Authenticator.hpp"

Authenticator::Authenticator(/* args */){ 
    this->data = new FAT();
}

Authenticator::~Authenticator() { }

bool Authenticator::autenticar(char *username, char * hash) {
    return this->data->searchCredentials(username, hash);
}