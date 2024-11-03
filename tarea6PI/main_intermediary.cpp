#include "Intermediary.hpp"
#include "networkConfig.hpp"

int main() {
  Intermediary node = Intermediary("log_intermediary.txt", 1, kIntermediaryPort);
  if(node.initServer()) {
    node.run();
    return 0;
  } else {
    return 1;
  }
}
