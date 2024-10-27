#include "Node.cpp"
int main() {
  Node node = Node(3000);
  if(node.initServer()) {
    node.run();
    return 0;
  } else {
    return 1;
  }
}
