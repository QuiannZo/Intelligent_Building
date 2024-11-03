#include "ClientNode.hpp"

// constructor
ClientNode::ClientNode(std::string logFilename, int processId) 
: Client(logFilename, processId) {}

// destructor
ClientNode::~ClientNode() {}
