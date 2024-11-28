#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <openssl/sha.h>

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

string generateHASH_SHA256(const string& password) {
    // See: https://stackoverflow.com/questions/918676/generate-sha-hash-in-c-using-openssl-library
    // https://docs.openssl.org/master/man3/SHA256_Init/

    unsigned char hash[SHA256_DIGEST_LENGTH]; // sha256 has a length of 32 bits
    // Cast the string to a unsigned char*
    const unsigned char* data = (const unsigned char*)password.c_str(); // cast
    SHA256(data, password.size(), hash); // get the sha256 hash
    stringstream ss;
    // convert to hexadecimal
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

#endif