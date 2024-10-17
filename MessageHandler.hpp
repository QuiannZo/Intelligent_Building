#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <vector>

enum nodes : uint8_t {
    CLIENT, BACKUP, ESP8266, AUTHENTICATOR, GALILEO, INTERMEDIARY, DATA 
};

enum messageType : uint8_t {
    CONFIRMATION, STATUS, /*qué exactamente*/ PASSWORDUSERNAMEAUTH, LARGEDATA
};

enum sensorData : uint8_t {
    DATE, TIME, TEMPERATURE, ULTRASONIC/*no sirve, lo simulamos?*/, PHOTORESISTOR, IRC 
};

class MessageHandler {
private:
    
public:
    MessageHandler();
    ~MessageHandler();
    
};

#endif