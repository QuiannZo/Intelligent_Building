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
    objectFAT->print(true);
    std::cout << std::endl;
    std::cout << "********** (2) Imprimir después de crear archivos (2) **********" << std::endl << std::endl;
    objectFAT->create(filename, date);
    objectFAT->print(true);
    objectFAT->open(filename, 7);
    std::cout << std::endl;

    Usuario myUser;

    std::cout << "********** (3) Imprimir después de agregar usuarios (3) **********" << std::endl << std::endl;
    objectFAT->write(filename, 7, (char*)"Chanchito hx9242\n");
    objectFAT->append(filename, 7, (char*)"Papita z22342\n");
    myUser.addUser("admin", "root1234", "1", "Quiann", "ZOlfaghari", "118700209", filename, objectFAT);
    objectFAT->print(true);
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
    

    // Sistemas operativos:
    /*
    Usuario myUser;

    std::cout << "* Imprimir después de agregar 10 usuarios *" << std::endl << std::endl;

    // Datos base para crear algunos usuarios.
    std::string user = "user";
    std::string passwordDefined = "pass";
    std::string permission = "1";
    std::string name = "Nombre";
    std::string lastname = "Apellido";
    std::string Id = "000000000";

    // Meter 10....
    for (int i = 1; i <= 10; i++) {
        std::string username = user + std::to_string(i);  // user1, user2, ...
        std::string password = passwordDefined + std::to_string(i);
        std::string id = Id + std::to_string(i);

        // Agregar:
        myUser.addUser(username, password, permission, name, lastname, id, filename, objectFAT);
    }

    // Imprimir el contenido del FAT después de agregar los usuarios
    objectFAT->print(true);
    std::cout << std::endl;

    cout << endl
        << "********** (3) Prueba de búsqueda (3) **********" << endl
        << endl;
    int searchResult = objectFAT->search((char *)"users.txt");
    if (searchResult != -1)
    {
    cout << "Archivo 'users.txt' encontrado en la posición: " << searchResult << endl;
    }
    else
    {
    cout << "Error: No se encontró el archivo 'users.txt'" << endl;
    }

    searchResult = objectFAT->search((char *)"inexistente.txt");
    if (searchResult == -1)
    {
    cout << "Correcto: 'inexistente.txt' no encontrado." << endl;
    }
    else
    {
    cout << "Error: archivo 'inexistente.txt' fue encontrado, lo cual es incorrecto." << endl;
    }

    // Prueba para el método 'renombrar' (rename)
    cout << endl
        << "********** (4) Prueba de renombrar (4) **********" << endl
        << endl;
    bool renameResult = objectFAT->rename((char *)"users.txt", (char *)"usuarios_renombrado.txt");
    if (renameResult)
    {
    cout << "Archivo renombrado a 'usuarios_renombrado.txt' exitosamente." << endl;
    }
    else
    {
    cout << "Error: No se pudo renombrar el archivo." << endl;
    }

    renameResult = objectFAT->rename((char *)"inexistente.txt", (char *)"nuevo_nombre.txt");
    if (!renameResult)
    {
    cout << "Correcto: no se puede renombrar un archivo inexistente." << endl;
    }
    else
    {
    cout << "Error: archivo inexistente renombrado incorrectamente." << endl;
    }

    // Prueba para el método 'leer' (read) antes de escribir
    cout << endl
        << "********** (5) Prueba de lectura antes de escribir en el archivo (5) **********" << endl
        << endl;
    char buffer[1000];
    bool readResult = objectFAT->read((char *)"usuarios_renombrado.txt", buffer, 7, 999);
    if (readResult)
    {
    cout << "Contenido leído: " << buffer << endl;
    }
    else
    {
    cout << "Error: no se pudo leer el archivo." << endl;
    }

    readResult = objectFAT->read((char *)"inexistente.txt", buffer, 7, 99);
    if (!readResult)
    {
    cout << "Correcto: no se puede leer un archivo inexistente." << endl;
    }
    else
    {
    cout << "Error: lectura incorrecta de un archivo inexistente." << endl;
    }

    // Prueba para el método 'escribir' (write)
    cout << endl
        << "********** (6) Prueba de escritura (6) **********" << endl
        << endl;
    bool writeResult = objectFAT->write((char *)"usuarios_renombrado.txt", 7, (char *)" Nuevo contenido de prueba.\n");
    if (writeResult)
    {
    cout << "Escritura exitosa." << endl; 
    }
    else
    {
    cout << "Error: no se pudo escribir en el archivo." << endl;
    }

    cout << endl;

    // Prueba para el método 'leer' despùes de escribir (read) después de leer
    cout << endl
        << "********** (7) Prueba de lectura después de escribir en el archivo (7) **********" << endl
        << endl;
    readResult = objectFAT->read((char *)"usuarios_renombrado.txt", buffer, 7, 50);
    if (readResult)
    {
    cout << "Contenido leído: " << buffer << endl;
    }
    else
    {
    cout << "Error: no se pudo leer el archivo." << endl;
    }


    if (objectFAT->close((char*)"usuarios_renombrado.txt", 7)) {
    std::cout << "Se cerró exitosamente el archivo." << std::endl;
    }
    */

    return 0;
}