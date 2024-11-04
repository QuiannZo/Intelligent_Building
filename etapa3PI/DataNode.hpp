#ifndef DATA_NODE_HPP
#define DATA_NODE_HPP

#include "Node.hpp"
#include "socketList.hpp"
#include "networkConfig.hpp"

using namespace std;

class DataNode : public Node{
    private:
        std::string sensorFilename;
    public:
        DataNode(std::string logFilename, int processId, std::string sensorFilename, int port);
        ~DataNode();
        std::string returnSensorFile(std::string username);
        bool handleDatagram(int client_socket, char *datagram, size_t datagram_size);
    };


#endif