#include "Usuario.hpp"


#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

// **Username, password, permission, name, lastname, id. De momento date lo deje default, es agregarlo despues.
void Usuario::addUser(std::string pUserName, std::string pPassword, std::string pPermission, std::string pName, 
std::string pLastname, std::string pId, char* filename, FAT* myFat) {
  // std::setw y std::setfill para llenar con espacios lo que no se use.
  std::ostringstream oss;
  oss << std::left << std::setw(20) << pUserName
      << std::setw(20) << pPassword
      << std::setw(1)  << pPermission // 0 = read, 1 = read and write.
      << std::setw(20) << pName
      << std::setw(20) << pLastname
      << std::setw(10) << pId;

  std::string content = oss.str();

  char data[91];
  strcpy(data, content.c_str());  // Convertir la cadena final a char array

  int index = myFat->search(filename);
  if (index == -1) {
      myFat->create(filename, (char *)"12/12/2012");
      myFat->open(filename, 7);
  }
  
  // Guardar los datos en el archivo del FAT
  myFat->append(filename, 7, data);
}

void Usuario::print(bool verbose) {
    std::cout << "*** User infomation ***" << std::endl;
    if (verbose) {
        std::cout << "User is:  " << userName << std::endl;
        std::cout << "Password with hash is: " << userPasswordHash << std::endl;
    }
    std::cout << std::endl;
}

std::string Usuario::hash(std::string password) {
  std::string pHash;
  pHash = "";
  for (int i = 0; i < password.length(); ++i) {
    int ascii_value = password[i]; // Conversión implícita de char a int
    ascii_value += 3;
    char ascii_char = ascii_value;
    pHash = pHash + ascii_char;
  }
  return pHash;
}
