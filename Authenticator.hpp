#include <iostream>
#include <cstring>

#include "FAT.hpp"

#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

enum permissions : uint8_t {
    // Next, we show the bits corresponding to each `user type` / permission
    USER_ADMINISTRATOR = 1, // bits: 00000001
    DATABASE_ADMINISTRATOR = 2, // bits: 00000010
    FLOOR_MANAGER = 4, // bits: 00000100
    BUILDING_MANAGER = 8, // bits: 00001000
    SYSTEM_ADMINISTRATOR = 16, // bits: 00010000
    AUDITOR = 32 // bits: 00100000
    /**
     * - To build a permission for a user with more than one permission, use the bitwise AND (&) operator. 
     *     Example: USER_ADMINISTRATOR & AUDITOR
     * - To verify that a user has a permission, use bitwise OR (|) operator against the corresponding permission,
     * then compare the result and the permission.
     *     Example: user_info | AUDITOR == AUDITOR
    */ 
};

class Authenticator {
private:
   FAT* data;

public:
    Authenticator(/* args */);
    ~Authenticator();
    // Methods
    bool autenticar(char *username, char * hash);
    FAT* getData() { return data; }
};
#endif