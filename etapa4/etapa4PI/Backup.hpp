#ifndef BACKUP_HPP
#define BACKUP_HPP

#include "Node.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

using namespace std;

class Backup : public Node{
    private:
        std::string sensorFilename;
    public:
        Backup(std::string logFilename, int processId, std::string sensorFilename, int port);
        ~Backup();
        std::string returnSensorFile(std::string username);
        bool handleDatagram(int client_socket, char *datagram, size_t datagram_size);
    };


#endif