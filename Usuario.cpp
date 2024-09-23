#include "Usuario.hpp"
#include "FAT.hpp"

#include <string>
#include <fstream>
#include <iostream>

void Usuario::addUser(std::string pUserName, std::string pPassword, char* filename) {
  userName = pUserName;
  userPassword = pPassword;
  userPasswordHash = hash(pPassword);
  char data[100];
  FAT myFat;
  char *date = (char *)"12/12/2012";
  size_t strLength = std::strlen(date);
  int index = myFat.search(filename);
  if (index == -1) {
    myFat.create(filename, date);
    myFat.open(filename, 7);
  }
  std::string content = pUserName + " " + userPasswordHash + " " + "\n";
  strcpy(data, content.c_str());
  myFat.append(filename, 7, data);
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
