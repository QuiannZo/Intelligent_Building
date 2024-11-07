#include <SPI.h>
#include <Ethernet.h>
#include <iostream>
#include <cstring>

// Configuración de la red
uint8_t mac[] = { 0x98, 0x4F, 0xEE, 0x00, 0xCD, 0xC2 };  // Dirección MAC como uint8_t
IPAddress server(192, 168, 0, 100);  // IP del servidor destino
int serverPort = 3002;  // Puerto del servidor

EthernetClient client;  // Cliente Ethernet

// Estructura para almacenar los datos del sensor
struct SensorData {
    uint8_t message_type;  // En lugar de MessageType
    uint8_t source_node;   // En lugar de NodeType
    char sensor_type[17];
    char sensor_id[17];
    int value;
};

// Clase GalileoClient
class GalileoClient {
public:
    GalileoClient() {}
    // Método para enviar datos de sensores al servidor
    bool sendSensorDataToUserHandler(const SensorData& sensor_data) {
        Serial.println("Inside send(). ");
        // Intentar conectar al servidor
        if (client.connect(server, serverPort)) {
            Serial.println("Inside connect(). ");
            // Serializar el objeto sensor_data en un datagrama
            char datagram[sizeof(SensorData)];
            std::memcpy(datagram, &sensor_data, sizeof(SensorData));

            // Enviar el datagrama
            if (client.write(reinterpret_cast<const uint8_t*>(datagram), sizeof(SensorData)) != sizeof(SensorData)) {
                Serial.println("Error sending datagram to server");
                client.stop();
                return false;
            }
            // Cerrar la conexión
            client.stop();
            Serial.println("Datagram sent to server and connection closed.");
            return true;
        } else {
            Serial.println("Error connecting to server");
            return false;
        }
    }
};

// Configuración de la red Ethernet
void setup() {
    Serial.begin(9600);

    // Iniciar la conexión Ethernet
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        while (true);
    }

    // Esperar a que se establezca la conexión
    delay(1000);
    Serial.println("Ethernet connected!");

    // Mostrar la dirección IP asignada por DHCP
    Serial.print("IP Address: ");
    Serial.println(Ethernet.localIP());
}

void loop() {
    Serial.print("Step 1: ");
    // Crear un ejemplo de datos de sensor
    SensorData photo_data = createPhotoSensorData("photo_sensor_7");
    SensorData ir_Data = createIRSensorData("ir_sensor_5");
    SensorData humidity_Data = createHumidityData("hum_sensor_4");
    SensorData temp_Data = createIRTemperatureData("temp_sensor_4");

    // Crear el cliente Galileo y enviar los datos
    GalileoClient client;
    client.sendSensorDataToUserHandler(photo_data);
    client.sendSensorDataToUserHandler(ir_Data);
    client.sendSensorDataToUserHandler(humidity_Data);
    client.sendSensorDataToUserHandler(temp_Data);
    Serial.print("Step 2: ");
    delay(30000);  // Esperar 30 segundos antes de enviar nuevamente
}

// Función para crear datos de un sensor
SensorData createPhotoSensorData(const std::string& sensor_id) {
    SensorData data;
    data.message_type = (uint8_t)36; // kSensorData <- 36U 
    data.source_node = (uint8_t)7;  // kIntelGalileo <- 7U
    strcpy(data.sensor_type, "PhotoSensor");
    strcpy(data.sensor_id, sensor_id.c_str());
    data.value = rand() % 1024;  // Generar un valor aleatorio para el sensor
    return data;
}

// Función para crear datos de un sensor
SensorData createIRSensorData(const std::string& sensor_id) {
    Serial.print("Build struct. ");
    SensorData data;
    data.message_type = (uint8_t)36; // kSensorData <- 36U 
    data.source_node = (uint8_t)7;  // kIntelGalileo <- 7U
    strcpy(data.sensor_type, "IR");
    strcpy(data.sensor_id, sensor_id.c_str());
    data.value = rand() % 1024;  // Generar un valor aleatorio para el sensor
    Serial.print("Struct Builded. ");
    return data;
}

// Función para crear datos de un sensor
SensorData createHumidityData(const std::string& sensor_id) {
    SensorData data;
    data.message_type = (uint8_t)36; // kSensorData <- 36U 
    data.source_node = (uint8_t)7;  // kIntelGalileo <- 7U
    strcpy(data.sensor_type, "Humidity");
    strcpy(data.sensor_id, sensor_id.c_str());
    data.value = rand() % 100;  // Generar un valor aleatorio para el sensor
    return data;
}

// Función para crear datos de un sensor
SensorData createIRTemperatureData(const std::string& sensor_id) {
    SensorData data;
    data.message_type = (uint8_t)36; // kSensorData <- 36U 
    data.source_node = (uint8_t)7;  // kIntelGalileo <- 7U
    strcpy(data.sensor_type, "Temp");
    strcpy(data.sensor_id, sensor_id.c_str());
    data.value = rand() % 100;  // Generar un valor aleatorio para el sensor
    return data;
}





