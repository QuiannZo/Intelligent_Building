#include <openssl/sha.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "HashHandler.hpp"

HashHandler::HashHandler() {
}

HashHandler::~HashHandler() {
}

// Function to generate a hash from a password using SHA-256
// We are not using a 'salt'
std::string HashHandler::generateHASH_SHA256(const std::string& password) {
    // See: https://stackoverflow.com/questions/918676/generate-sha-hash-in-c-using-openssl-library
    // https://docs.openssl.org/master/man3/SHA256_Init/

    unsigned char hash[SHA256_DIGEST_LENGTH]; // sha256 has a length of 32 bits
    // Cast the string to a unsigned char*
    const unsigned char* data = (const unsigned char*)password.c_str(); // cast
    SHA256(data, password.size(), hash); // get the sha256 hash
    std::stringstream ss;
    // convert to hexadecimal
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
// Function to validate the password
bool HashHandler::validatePassword_SHA256(const std::string &password, const std::string &originalHash) {
    // Generate hash for the input password
    std::string new_hash = generateHASH_SHA256(password);
    // Compare the new hash with the original hash
    return new_hash == originalHash;
}
