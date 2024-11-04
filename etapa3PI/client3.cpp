
#include "ClientNode.hpp" 

int main() {
  ClientNode client("log_client.txt", 1);
  std::vector<std::string> result;
  // Usuario invalido:
  client.authenticateUser("username", "password", result);
  // Usuario valido 
  client.authenticateUser("username07", "password07", result);
  return 0;
}