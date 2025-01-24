#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std ;

// dividir tokens de la línea de comandos
vector<string> dividir(const char* str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ' ')) {
      if (!token.empty()) {  
          tokens.push_back(token);
      }
    }
    return tokens;
}