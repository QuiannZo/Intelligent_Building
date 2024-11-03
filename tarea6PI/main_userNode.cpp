#include "UserNode.cpp"
#include "networkConfig.hpp"

int main() {
  UserNode node = UserNode("log_UserNode.txt", 1, "usersData.txt", kUserHandlerPort);
  if(node.initServer()) {
    node.run();
    return 0;
  } else {
    return 1;
  }
}