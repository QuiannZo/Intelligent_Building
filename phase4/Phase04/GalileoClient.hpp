#ifndef GALILEO_CLIENT_HPP
#define GALILEO_CLIENT_HPP

#include "Client.hpp"
#include "socketList.hpp"

class GalileoClient {
private:
  int generateRandom(int min, int max);
  SensorData createPhotoSensorData(const std::string& sensor_id);
  SensorData createIRSensorData(const std::string& sensor_id);
  SensorData createHumiditySensorData(const std::string& sensor_id);
  SensorData createTemperatureSensorData(const std::string& sensor_id);
public:
  bool sendSensorDataToUserHandler(const SensorData& sensor_data);
  GalileoClient(std::string logFilename, int processId);
  ~GalileoClient();


};


#endif