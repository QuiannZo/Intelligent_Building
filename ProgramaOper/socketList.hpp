#ifndef SOCKET_LIST
#define SOCKET_LIST

#include <cstdint>

// TamaÃ±o mÃ¡ximo del datagrama
const int kMaxDatagramSize = 512;

// Tipos de nodos que con capacidad de comunicaciÃ³n en la sistema distribuido
enum NodeType : uint8_t {
  kTest,
  kApplication,
  kIntermediary,
  kUserHandler,
  KDataCollector,
  kBackupServer,
  kEsp8266,
  kIntelGalileo
};

// Tipos de mensajes en el sistema distribuido
enum MessageType : uint8_t {
  // Mensajes generales:
  kInvalidRequest,
  kCommunicationError,
  kUnknownError,
  kLongFileHeader, 
  kTransmissionError, 
  // Mensajes entre cliente <-> `Intermediary` <-> `UserHandler`:
  kAuthenticationRequestCI,
  kAuthenticationSuccessIC,
  kAuthenticationFailure,
  // Mensajes `UserHandler` <-> `Intermediary`
  kAuthenticationRequestIU,
  kAuthenticationSuccessUI,
  // Mensajes que cliente envÃ­a a intermediario, para solicitud de informaciÃ³n.
  kLogRequestCI,
  kUserListRequestCI,
  kSensorInfoRequestCI,
  kDistributedSystemInfoRequestCI,
  kBackupServerStatusRequestCI,
  // Mensajes que cliente envÃ­a a intermediario y viceversa, para modificar o agregar usuarios.
  kAddUserRequestCI,
  kModifyUserRequestCI,
  kActivateDeactivateUserRequestCI,
  //kUserChangesConfirmationIC,
  kUserChangesConfirmation,
  kUserInfoRequestCI,
  kUserInfoResponseIC,
  kUserRequestFailureIC,
  // Mensajes que intermediario envÃ­a a UserHandler y viceversa, 
  // con las peticiones hechas por el cliente.
  kLogRequestIU,
  kUserListRequestIU,
  kAddUserRequestIU,
  kModifyUserRequestIU,
  kActivateDeactivateUserRequestIU,
  //kUserChangesConfirmationUI,
  kUserInfoRequestIU,
  kUserInfoResponseUI,
  // Mensajes entre `Intermediary`y `DataCollector`:
  kLogRequestID,
  kSensorInfoRequestID,
  kSensorStatusRequestID,
  // Mensajes entre `Intermediary` y `Backup_server`:
  kBackupServerStatusRequestIB,
  // Mensajes entre `DataCollector` e `Intel Galileo:
  kSensorStatusRequestDG,
  kSensorInfoResponseGD,
  kSensorInfoConfirmationDG,
  kSensorData, // nuevo
  // Mensajes entre `Intel Galileo` y `ESP8266`:
  kSensorInfoRequestGE,
  kSensorInfoResponseEG,
  // Mensajes entre `Backup_server` y `DataCollector` / `UserHandler`:
  kFileRequestBDU,
  kRequestFailureDUB,
  kRequest
};

// Datagramas generales:
struct InvalidRequest {
  // Mensaje con el que responde un nodo cuando no puede manejar una datagrama
  // recibido previamente. 
  MessageType message_type;
  NodeType source_node;
};

// Datagramas generales:
struct CommunicationError {
  // Mensaje con el que responde un nodo cuando no puede manejar una datagrama
  // recibido previamente. 
  MessageType message_type;
  NodeType source_node;
  NodeType error_node;
};

struct LongFileHeader {
  // Mensaje que indicar el tamaÃ±o del archivo que vamos a enviar. Inmediatamente
  // despuÃ©s se envÃ­a el mensaje por el socket. 
  MessageType message_type;
  NodeType source_node;
  bool successful;
  int char_length;
};


// Datagramas entre cliente e `Intermediary`:
// >> De cliente a intermediario:
struct AuthenticationRequest {
  // Mensaje de consulta de autenticaciÃ³n: mensaje que envÃ­a el cliente con el
  // nombre de usuario y hash para autenticar un usuario. 
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char hash[65];
  // TamaÃ±o: 100 bytes
};

// >> De intermediario a cliente:
struct AuthenticationSuccessIC {
  // Mensaje de confirmaciÃ³n afirmativa de autenticaciÃ³n: mensaje que viaja del
  // `Intermediary` al cliente cuando el usuario fue autenticado correctamente.
  MessageType message_type;
  NodeType source_node;
  char name[33];
  char last_name[33];
  uint8_t permissions;
  // int16_t user_id;
  // TamaÃ±o: 71 bytes
};

struct AuthenticationFailure {
  // Mensaje de confirmaciÃ³n negativa de autenticaciÃ³n: mensaje que viaja del
  // intermediario al cliente cuando el usuario o el hash son invÃ¡lidos,
  // incluye el tipo de error. 
  MessageType message_type;
  NodeType source_node;
  char error[65];
  // TamaÃ±o: 3 bytes
};

struct AuthenticationSuccessUI {
  // Mensaje de confirmaciÃ³n afirmativa de autenticaciÃ³n: mensaje que viaja
  // entre el `Intermediary` y `UserHandler` indicando que la autenticaciÃ³n
  // fue exitosa. Incluye permisos, nombres y apellidos de usuario.
  MessageType message_type;
  NodeType source_node;
  char name[33];
  char last_name[33];
  uint8_t permissions;
  // TamaÃ±o: 71 bytes
};

// Datagramas que intermediario envÃ­a a UserHandler y viceversa, 
// con las peticiones hechas por el cliente.

struct LogRequestCI {
  // Mensaje del cliente al intermediario, para pedir bitÃ¡cora.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
  NodeType node_required;
  uint16_t user_identification;
};

struct UserListRequestCI {
  // El cliente pide al intermediario solicitud de la lista de usuarios.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
  uint16_t user_identification;
};

struct SensorInfoRequestCI {
  // El cliente pide al intermediario solicitud de informaciÃ³n de los sensores.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
  uint16_t user_identification;
};

struct DistributedSystemInfoRequestCI {
  // El cliente pide al intermediario solicitud del estado del sistema distribuido.
  MessageType message_type;
  NodeType source_node;
  uint16_t user_identification;
};

struct BackupServerStatusRequestCI {
  // El cliente pide al intermediario solicitud del estado de las copias de seguridad.
  MessageType message_type;
  NodeType source_node;
  uint16_t user_identification;
};


 // Datagramas que cliente envÃ­a a intermediario y viceversa, para modificar o agregar usuarios.

struct AddUserRequestCI {
  // El cliente envÃ­a solicitud al intermediario, para poder agregar un usuario.
  MessageType message_type;
  NodeType source_node;
  char  addedByUser[33];
  char username[33];
  char hash[65];
  char name[33];
  char last_name[33];
  uint8_t permissions;
  int8_t floors[32];
  uint16_t user_identification;
};

struct ModifyUserRequestCI {
  // El cliente envÃ­a solicitud al intermediario, para poder modificar un usuario.
  MessageType message_type;
  NodeType source_node;
  char modify_by[33];
  char current_username[33];
  char new_username[33];
  char new_hash[65];
  char new_name[33];
  char new_last_name[33];
  uint8_t new_permissions;
  int8_t new_floors[32];
  uint16_t user_identification;
};

struct ActivateDeactivateUserRequestCI {
  // El cliente envÃ­a solicitud al intermediario, para poder activar 
  // o desactivar un usuario.
  MessageType message_type;
  NodeType source_node;
  uint16_t user_identification;
  char username[33];
  uint8_t status;
};

struct UserChangesConfirmation {
  // El intermediario le envÃ­a una respuesta al cliente, despuÃ©s de que 
  // el UserHandler haya modificado, agregado o cambiado el estado de 
  // los usuarios.
  MessageType message_type;
  NodeType source_node;
  bool successful;
  char error[65];
};

struct UserInfoRequestCI {
  // El cliente envÃ­a solicitud al intermediario, para poder obtener
  // informaciÃ³n de un usuario.
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char request_by[33];
  uint16_t user_identification;
};


struct UserRequestFailureIC {
  // Intemediario envÃ­a mensaje de rechazo a la peticiÃ³n del cliente.
  MessageType message_type;
  NodeType source_node;
  uint8_t rejected_message_type;
  char username[33];
};

// Datagramas que intermediario envÃ­a a UserHandler y viceversa, 
// con las peticiones hechas por el cliente.

struct LogRequestIN {
  // Mensaje del intermediario al a un nodo, para pedir bitÃ¡cora.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
};

struct UserListRequestIU {
  // El intermediario pide al user handler solicitud de la lista de usuarios.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
};

struct AddUserRequestIU {
  // El cliente envÃ­a solicitud al intermediario, para poder agregar un usuario.
  MessageType message_type;
  NodeType source_node;
  char  addedByUser[33];
  char username[33];
  char hash[65];
  char name[33];
  char last_name[33];
  uint8_t permissions;
  int8_t floors[32];
};

struct ModifyUserRequestIU {
  // El intermediario envÃ­a solicitud al user handler, para poder modificar un usuario.
  MessageType message_type;
  NodeType source_node;
  char modify_by[33];
  char current_username[33];
  char new_username[33];
  char new_hash[65];
  char new_name[33];
  char new_last_name[33];
  uint8_t new_permissions;
  int8_t new_floors[32];
};

struct ActivateDeactivateUserRequestIU {
  // El intermediario envÃ­a solicitud al user handler, para poder activar 
  // o desactivar un usuario.
  MessageType message_type;
  NodeType source_node;
  uint16_t user_identification;
  char username[33];
  uint16_t client_identification;
  uint8_t status;
};

struct UserInfoRequestIU {
  // El intermediario envÃ­a solicitud al user handler, para poder obtener
  // informaciÃ³n de un usuario.
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char request_by[33];
};

struct UserInfoResponse {
  // Mensaje que va del user handler al intermediario, con la informaciÃ³n
  // del usuario solicitado.
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char name[33];
  char last_name[33];
  uint8_t permissions;
  bool is_active;
  bool successful;
  char error[65];
};

// Datagramas entre `Intermediary`y `DataCollector`:


struct SensorInfoRequestID {
  // El intermediario pide al data collector solicitud de informaciÃ³n de los sensores.
  MessageType message_type;
  NodeType source_node;
  char request_by[33];
};

struct SensorStatusRequestID {
  // El intermediario le solicita estado de los sensores al data collector.
  MessageType message_type;
  NodeType source_node;
  NodeType requested_node;
};

// Datagramas entre `Intermediary` y `Backup_server`:
struct BackupServerStatusRequestIB {
  // Intermediario pide estado de las copias de seguridad al backup server.
  MessageType message_type;
  NodeType source_node;
  uint16_t client_identification;
};

// Datagramas entre `DataCollector` e `Intel Galileo:
struct SensorStatusRequestDG {
  // Mensaje que envÃ­a el data collector al intel galileo,
  // para obtener informaciÃ³n de los sensores.
  MessageType message_type;
  NodeType source_node;
  NodeType requested_node;
};

struct SensorInfoResponseGD {
  // Se envÃ­an los datos del intel galileo, al data collector.
  MessageType message_type;
  NodeType source_node;
  uint8_t sensorType;
  uint8_t sensor_id;
  char time[8];
  char date[8];
  char measure_value[8];
};

struct SensorInfoConfirmationDG {
  // El data collector le confirma al galileo el recibido de los datos
  MessageType message_type;
  NodeType source_node;
  uint8_t sensorType;
  uint8_t sensor_id;
};

// Datagramas entre `Intel Galileo` y `ESP8266`:
struct SensorInfoRequestGE {
  // El intel galileo solicita informaciÃ³n a los ESP8266.
  MessageType message_type;
  NodeType source_node;
  uint8_t requested_sensor;
};

struct SensorInfoResponseEG {
  // Los ESP8266 envÃ­an la informaciÃ³n al intel galileo.
  MessageType message_type;
  NodeType source_node;
  char time[8];
  char date[8];
  char measure_value[8];
};

// Datagramas entre `Backup_server` y `DataCollector` / `UserHandler`:
struct FileRequestBDU {
  // El backup server solicita un archivo a los nodos data collector
  // y user handler.
  MessageType message_type;
  NodeType source_node;
  char filename[100];
};

struct RequestFailureDUB {
  // El data collector o user handler envÃ­an mensaje de error
  // al backup server
  MessageType message_type;
  NodeType source_node;
  uint8_t error;
};

// Nuevo
struct SensorData {
  MessageType message_type;
  NodeType source_node;
  char sensor_type[17];
  char sensor_id[17];
  int value;
};

# endif