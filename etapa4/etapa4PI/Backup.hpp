#ifndef BACKUP_HPP
#define BACKUP_HPP

#include "Node.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

using namespace std;

class Backup : public Node{
    private:
        std::string updateLogDataNode;
        std::string updateLogIntermediary;
        std::string updateLogUser;
        std::string updateSensorsInfo;
        std::string updateUserInfo;

        string receivedLogDataNode;
    public:
        // Cambiar constructor 
        Backup(std::string logFilename, int processId, int port);
        ~Backup();
        bool handleDatagram(int client_socket, char *datagram, size_t datagram_size);
        void run();
        void requestSaveFiles();
        void saveFile(string filename, string data);
    };


#endif