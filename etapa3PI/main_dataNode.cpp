#include <csignal>
#include <iostream> 
#include "DataNode.hpp"
#include "networkConfig.hpp"

// Manejo de control + c: basado en https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
// Puntero global
DataNode* node = nullptr;

void signalControlCHandler(int signum) {
  if (node) {
    delete node;
  }
  std::exit(signum); 
}

int main() {
  DataNode* node = new DataNode("log_DataNode.txt", 1, "sensors_log_file", kDataNodePort);
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