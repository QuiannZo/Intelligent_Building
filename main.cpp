#include "FAT.hpp"
#include "Usuario.hpp"
#include "Autenticador.hpp"
#include <cstring>
#include <iostream>

using namespace std;

int main() {
  Autenticador objectA;
  FAT objectFAT = objectA.getData();
  char *filename = (char *)"test.txt";
  char *date = (char *)"12/12/2012";
  char *proof = (char *)"12/aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccccccccccc12/12";
  bool result4 = objectFAT.create(filename, date);
  int result = objectFAT.search(filename);
  bool result2 = objectFAT.open(filename, 7);
  bool result5 = objectFAT.write(filename, 7, proof);
 

  Usuario myUser;
  myUser.addUser("admin", "root", filename, objectFAT);
  myUser.print(true);
  
  char *username = (char *)"admin";
  char *hash = (char *)"urrw";
  
  objectA.autenticar(username, hash);
   
  objectFAT.print(true);
  bool result3 = objectFAT.close(filename, 7);

  if (result > -1) {
    std::cout << "funciona search" << std::endl;
    ;
  }

  if (result2) {
    std::cout << "funciona open" << std::endl;
    ;
  }

  if (result3) {
    std::cout << "funciona close" << std::endl;
    ;
  }

  if (result4) {
    std::cout << "funciona create" << std::endl;
    ;
  }

  if (result5) {
    std::cout << "funciona write" << std::endl;
    ;
  }

  return 0;
}