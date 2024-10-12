#include "FAT.hpp"
#include "Usuario.hpp"
#include "Autenticador.hpp"
#include <cstring>
#include <iostream>

int main(){
    Authenticator objectA;
    FAT* objectFAT = objectA.getData();
    char *filename = (char *)"users.txt";

    Usuario myUser;

    std::cout << "* Imprimir después de agregar 10 usuarios *" << std::endl << std::endl;

    // Datos base para crear algunos usuarios.
    std::string user = "user";
    std::string password = "pass";
    std::string permission = "1";
    std::string name = "Nombre";
    std::string lastname = "Apellido";
    std::string Id = "000000000";

    // Meter 10....
    for (int i = 1; i <= 10; i++) {
        std::string username = user + std::to_string(i);  // user1, user2, ...
        std::string password = password + std::to_string(i);
        std::string id = Id + std::to_string(i);

        // Agregar:
        myUser.addUser(username, password, permission, name, lastname, id, filename, objectFAT);
    }

    // Imprimir el contenido del FAT después de agregar los usuarios
    objectFAT->print(true);
    std::cout << std::endl;

    // Close.
    objectFAT->close(filename, 7);

    return 0;
}