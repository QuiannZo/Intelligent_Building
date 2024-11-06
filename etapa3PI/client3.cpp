
#include "ClientNode.hpp" 

int main() {
  ClientNode client("log_client.txt", 1);
  std::vector<std::string> result;
  // Usuario invalido:
  //client.authenticateUser("username", "password", result);
  // Usuario valido 
  //client.authenticateUser("username07", "password07", result);
  //uint8_t permissions = 1 | 2;
  //int8_t floors[32];
  //floors[0] = 1;
  //floors[1] = 2;
  //floors[2] = 3;
  //floors[4] = 0; //terminación
  //std::string response;
  //client.addUser("superuser", "PruebaXYZ", "PasswordXYZ", permissions, floors, "Juan", "Perez", response);
  //client.modifyUser("superuser", "PruebaXYZ", "PruebaWXYZ", "PasswordXYZ", permissions, floors, "Juan", "Perez", response);
  //modificación invalida:
  //client.modifyUser("superuser", "PruebaXYZ", "PruebaWXYZ", "PasswordXYZ", permissions, floors, "Juan", "Perez", response);
  //client.getUserList("superuser", result);
  // Usuario no valido
  //client.getUserInformation("superuser", "Jose", result);
  // Usuario valido
  //client.getUserInformation("superuser", "PruebaWXYZ", result);
  std::string response;
  client.getSensorData("superuser", response);
  return 0;
}