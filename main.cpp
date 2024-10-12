#include "Authenticator.hpp"
#include "FAT.hpp"
#include "Usuario.hpp"
#include <cstring>
#include <iostream>

using namespace std;

int main() {
    Authenticator objectA;
    FAT* objectFAT = objectA.getData();
    char *filename = (char *)"users.txt";
    char *date = (char *)"12/12/2012";
    objectFAT->create(filename, date);
    objectFAT->open(filename, 7);
    // Presentación PI

    std::cout << "********** (1) Imprimir antes de crear archivos y agregar usuarios (1) **********" << std::endl << std::endl;
    //objectFAT->print(true);
    std::cout << std::endl;
    std::cout << "********** (2) Imprimir después de crear archivos (2) **********" << std::endl << std::endl;
    objectFAT->create(filename, date);
    //objectFAT->print(true);
    objectFAT->open(filename, 7);
    std::cout << std::endl;

    Usuario myUser;

    std::cout << "********** (3) Imprimir después de agregar usuarios (3) **********" << std::endl << std::endl;
    objectFAT->write(filename, 7, (char*)"Chanchito hx9242\n");
    objectFAT->append(filename, 7, (char*)"Papita z22342\n");
    myUser.addUser("admin", "root1234", "1", "Quiann", "ZOlfaghari", "118700209", filename, objectFAT);
    //objectFAT->print(true);
    std::cout << std::endl;
    //myUser.print(true);

    std::cout << "********** (4) Verificación (4) **********" << std::endl << std::endl;
    bool autenticado = objectA.autenticar((char *)"admin", (char *)"urrw");
    if (autenticado) {
        std::cout << "admin" << ": usuario verificado!" << std::endl;
    } else { 
        std::cout << "admin" << ": usuario no verificado!" << std::endl;
    }
    autenticado = objectA.autenticar((char *)"Papita", (char *)"z22342");
    if (autenticado) {
        std::cout << "Papita" << ": usuario verificado!" << std::endl;
    } else { 
        std::cout << "Papita" << ": usuario no verificado!" << std::endl;
    }

    objectFAT->loadFile((char *)"FormatoBitacora.txt", 7);
    objectFAT->print(true);

    objectFAT->open((char *)"FormatoBitacora.txt", 8);
    if(objectFAT->saveFile((char *)"FormatoBitacora.txt", 8, (char *)"proof.txt")) {
        std::cout << "Guardado exitosamente" << std::endl;
    }
    objectFAT->close((char *)"FormatoBitacora.txt", 8);
    // get line
    objectFAT->open((char *)"FormatoBitacora.txt", 8);
    char buffer[200];
    objectFAT->getLine((char *)"FormatoBitacora.txt", buffer, 200, 8);
    std::cout << buffer;
    objectFAT->getLine((char *)"FormatoBitacora.txt", buffer, 200, 8);
    std::cout << buffer;
    objectFAT->close((char *)"FormatoBitacora.txt", 8);
    std::cout << "Tamaño del archivo en chrs " <<  objectFAT->getFileSize((char *)"FormatoBitacora.txt") << std::endl;

    return 0;
}