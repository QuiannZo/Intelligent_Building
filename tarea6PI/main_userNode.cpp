#include "UserNode.cpp"
#include "networkConfig.hpp"

int main() {
  UserNode node = UserNode(kUserHandlerPort);
  if(node.initServer()) {
    node.run();
    return 0;
  } else {
    return 1;
  }
}