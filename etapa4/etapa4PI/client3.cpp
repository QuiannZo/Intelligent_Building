
#include "ClientNode.hpp" 

int main() {
  ClientNode client("log_client.txt", 1);
  std::vector<std::string> result;
 
  std::string response;
  //client.getBackupState("superUser", response);
  //client.getSystemState();
  client.activeDeactivateUser("superuser", "WarrenMI8", false, response);
  //int8_t floors[32];
  //client.addUser("asd", "asd", "asd", 1,floors, "asd", "asd", response);
  return 0;
}