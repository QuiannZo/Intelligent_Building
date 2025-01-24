#include <csignal>
#include <iostream> 
#include "Backup.hpp"
#include "networkConfig.hpp"

// Manejo de control + c: basado en https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
// Puntero global
Backup* node = nullptr;

void signalControlCHandler(int signum) {
  if (node) {
    delete node;
  }
  std::exit(signum); 
}

int main() {
  node = new Backup("log_BackupNode.txt", 1, kBackupPort);
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