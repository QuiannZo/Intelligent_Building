
#include "ClientNode.hpp" 

int main() {
  ClientNode client("log_client.txt", 1);
  std::vector<std::string> result;
 
  std::string response;
  //client.getBackupState("superUser", response);
  //client.getSystemState();
  client.activeDeactivateUser("superuser", "WarrenMI8", false, response);
  return 0;
}