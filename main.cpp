#include "FAT.hpp"
#include <cstring>
#include <iostream>

using namespace std;

int main() {
  FAT objectF;
  char *filename = (char *)"test.txt";
  char *date = (char *)"12/12/12";
  int result = objectF.search(filename);
  bool result2 = objectF.open(filename, 7);
  bool result3 = objectF.close(filename, 7);
  bool result4 = objectF.create(filename, date);

  if (result > -1) {
    std::cout << "funciona search" << std::endl;
    ;
  }

  if (result2) {
    std::cout << "funciona open" << std::endl;
    ;
  }

  if (result3) {
    std::cout << "funciona close" << std::endl;
    ;
  }

  if (result4) {
    std::cout << "funciona create" << std::endl;
    ;
  }

  return 0;
}