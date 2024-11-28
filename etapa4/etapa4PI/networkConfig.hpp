#ifndef NETWORK_CONFIG
#define NETWORK_CONFIG
// Dirección IP del localhost / computadora actual
const std::string kLocalhostIPv4 = "127.0.0.1";
const std::string kIntermediaryIPv4 = "10.1.35.20";
const std::string kUserHandlerIPv4 = "127.0.0.1";
const std::string kDataNodeIPv4 = "127.0.0.1";
const std::string kBackupNodeIPv4 = "127.0.0.1";

// Puertos:
// Puerto de nodo intermediario
const int kIntermediaryPort = 3000;
// Puerto del nodo UserHandler
const int kUserHandlerPort = 3001;
// Puerto del DataCollector
const int kDataNodePort = 3002;
// Puerto del Backup
const int kBackupPort = 3003;

#endif