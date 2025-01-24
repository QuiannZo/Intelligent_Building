#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "GalileoClient.hpp"
#include "networkConfig.hpp"

// Constructor
GalileoClient::GalileoClient(std::string logFilename, int processId) {}


// Destructor
GalileoClient::~GalileoClient() {
}

int GalileoClient::generateRandom(int min, int max) {
  return min + rand() % (max - min + 1);
}

// generar los datagramas con los valores de los sensores 
// Fotosensor
SensorData GalileoClient::createPhotoSensorData(const std::string& sensor_id) {
  SensorData data;
  data.message_type = kSensorData;
  data.source_node = kIntelGalileo;
  strcpy(data.sensor_type, "PhotoSensor");
  strcpy(data.sensor_id, sensor_id.c_str());
  data.value = generateRandom(0, 1023);
  return data;
}

// Infrarrojo 
SensorData GalileoClient::createIRSensorData(const std::string& sensor_id) {
  SensorData data;
  data.message_type = kSensorData;
  data.source_node = kIntelGalileo;
  strcpy(data.sensor_type, "IR");
  strcpy(data.sensor_id, sensor_id.c_str());
  data.value = generateRandom(0, 1023);  // Adjust range as needed
  return data;
}

// Humedad
SensorData GalileoClient::createHumiditySensorData(const std::string& sensor_id) {
  SensorData data;
  data.message_type = kSensorData;
  data.source_node = kIntelGalileo;
  strcpy(data.sensor_type, "Humidity");
  strcpy(data.sensor_id, sensor_id.c_str());
  data.value = generateRandom(0, 100);  // Percentage range
  return data;
}

// Temperatura 
SensorData GalileoClient::createTemperatureSensorData(const std::string& sensor_id) {
  SensorData data;
  data.message_type = kSensorData;
  data.source_node = kIntelGalileo;
  strcpy(data.sensor_type, "Temperature");
  strcpy(data.sensor_id, sensor_id.c_str());
  data.value = generateRandom(-20, 50);  // Adjust range as needed
  return data;
}

// Función para enviar datos de sensores al manejador de usuario
bool GalileoClient::sendSensorDataToUserHandler(const SensorData& sensor_data) {
  // Crear el socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
      std::cerr << "Error creating socket." << std::endl;
      return false;
  }
  // Configurar la dirección del servidor
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(kDataNodePort);
  // Convertir la IP a formato binario
  if (inet_pton(AF_INET, kDataNodeIPv4.c_str(), &server_address.sin_addr) <= 0) {
      std::cerr << "Invalid IP address: " << kDataNodeIPv4 << std::endl; // IP inválida
      close(client_socket);
      return false;
  }
  // Conectar al nodo UserHandler
  if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
      std::cerr << "Error connecting to UserHandler at " << kDataNodeIPv4 << ":" << kDataNodePort << std::endl; // Error al conectar
      close(client_socket);
      return false;
  }
  // Preparar el datagrama con los datos del sensor
  char datagram[sizeof(SensorData)];
  std::memcpy(datagram, &sensor_data, sizeof(SensorData));
  // Enviar el datagrama
  if (send(client_socket, datagram, sizeof(SensorData), 0) < 0) {
      std::cerr << "Error sending datagram to UserHandler." << std::endl; // Error al enviar el datagrama
      close(client_socket);
      return false;
  }
  // Cerrar la conexión inmediatamente después de enviar
  close(client_socket);
  std::cout << "Datagram sent to UserHandler and connection closed." << std::endl; // Mensaje de éxito
  return true;
}