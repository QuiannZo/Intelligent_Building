#include "FAT.hpp"
#include "Usuario.hpp"
#include "Autenticador.hpp"
#include <cstring>
#include <iostream>

using namespace std;

int main() {
  Autenticador objectA;
  FAT* objectFAT = objectA.getData();
  char *filename = (char *)"users.txt";
  char *date = (char *)"12/12/2012";
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
  myUser.addUser("admin", "root", filename, objectFAT);
  objectFAT->print(true);
  std::cout << std::endl;
  //myUser.print(true);

  std::cout << "********** (4) Verificación (4) **********" << std::endl << std::endl;
  bool autenticado = objectA.autenticar((char *)"admin", (char *)"urrw");
  if (autenticado) {
      std::cout << "admin" << ": usuario verificado!" << std::endl;
  } else { 
      std::cout << "admin" << "usuario no verificado!" << std::endl;
  }
  autenticado = objectA.autenticar((char *)"Papita", (char *)"mayonesa");
  if (autenticado) {
      std::cout << "Papita" << ": usuario verificado!" << std::endl;
  } else { 
      std::cout << "Papita" << ": usuario no verificado!" << std::endl;
  }

  objectFAT->close(filename, 7);

  return 0;
}