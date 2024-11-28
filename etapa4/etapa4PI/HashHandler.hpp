#ifndef HASH_HANDLER_HPP
#define HASH_HANDLER_HPP

#include <openssl/sha.h>
#include <string>

class HashHandler {
public:
    HashHandler();
    ~HashHandler();
    std::string generateHASH_SHA256(const std::string& password);
    bool validatePassword_SHA256(const std::string& password, const std::string& originalHash);
};

#endif
