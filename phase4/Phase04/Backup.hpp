#ifndef BACKUP_HPP
#define BACKUP_HPP

#include <thread>
#include <atomic>
#include "Node.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

using namespace std;

class Backup : public Node{
    private:
        // variables que se utilizan para guardar la ultima hora de backup
        std::string updateLogDataNode;
        std::string updateLogIntermediary;
        std::string updateLogUser;
        std::string updateSensorsInfo;
        std::string updateUserInfo;
        // Hilo que se encarga del backup:
        std::thread backupThread; 
        std::atomic<bool> running;
        std::atomic<int> minutesPassed;
        // función que corre el hilo de backup
        void backupTask();

    public:
        // Cambiar constructor 
        Backup(std::string logFilename, int processId, int port);
        ~Backup();
        bool handleDatagram(int client_socket, char *datagram, size_t datagram_size);
        void requestSaveFiles();
        void saveFile(string filename, string data);
    };


#endif