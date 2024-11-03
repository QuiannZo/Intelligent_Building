#include <csignal> 
#include <iostream>
#include "UserNode.cpp"
#include "networkConfig.hpp"

// Manejo de control + c: basado en https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
// Puntero global
UserNode* node = nullptr;

void signalControlCHandler(int signum) {
  if (node) {
    delete node;
  }
  std::exit(signum); 
}

int main() {
  UserNode* node = new UserNode("log_UserNode.txt", 1, "usersData.txt", kUserHandlerPort);
  signal(SIGINT, signalControlCHandler); 
  if(node->initServer()) {
    node->run();
    delete node;
    return 0;
  } else {
    delete node;
    return 1;
  }
}