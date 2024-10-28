#ifndef SOCKET_LIST
#define SOCKET_LIST

#include <cstdint>

// Tamaño máximo del datagrama
const int kMaxDatagramSize = 256;

// Tipos de nodos que con capacidad de comunicación en la sistema distribuido
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
  // Mensajes entre cliente <-> `Intermediary` <-> `UserHandler`:
  kAuthenticationRequestCI,
  kAuthenticationSuccessIC,
  kAuthenticationFailure,
  // Mensajes `UserHandler` <-> `Intermediary`
  kAuthenticationRequestIU,
  kAuthenticationSuccessUI,
  // Mensajes entre `Intermediary`y `UserHandler`:
  // Mensajes entre `Intermediary`y `DataCollector`:
  // Mensajes entre `Intermediary` y `Backup_server`:
  // Mensajes entre `DataCollector` e `Intel Galileo:
  // Mensajes entre `Intel Galileo` y `ESP8266`:
  // Mensajes entre `Backup_server` y `DataCollector` / `UserHandler`:
};

// TODO: volver a calcular tamaños de los datagramas
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

// TODO:completar.
// TODO: modificar descripción actual de los datagramas de acuerdo a los 
// cambios.
// Datagramas entre cliente e `Intermediary`:
// >> De cliente a intermediario:
struct AuthenticationRequest {
  // Mensaje de consulta de autenticación: mensaje que envía el cliente con el
  // nombre de usuario y hash para autenticar un usuario. 
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char hash[65];
  // Tamaño: 100 bytes
};

// >> De intermediario a cliente:
struct AuthenticationSuccessIC {
  // Mensaje de confirmación afirmativa de autenticación: mensaje que viaja del
  // `Intermediary` al cliente cuando el usuario fue autenticado correctamente.
  MessageType message_type;
  NodeType source_node;
  char name[33];
  char last_name[33];
  uint8_t permissions;
  // identificación de devuelve el intermediario, es usada por el el mismo 
  // para verificar que el usuario tenga la sesión iniciada. Es un sistema
  // sencillo diseñado para evitar autenticar el usuario en cada solicitud.
  // Por lo mismo, esta identificación debe ser usada por el cliente en
  // futuras peticiones. 
  uint16_t user_identification;
  // Tamaño: 71 bytes
};

struct AuthenticationFailure {
  // Mensaje de confirmación negativa de autenticación: mensaje que viaja del
  // intermediario al cliente cuando el usuario o el hash son inválidos,
  // incluye el tipo de error. 
  MessageType message_type;
  NodeType source_node;
  char error[65];
  // Tamaño: 3 bytes
};


struct AuthenticationSuccessUI {
  // Mensaje de confirmación afirmativa de autenticación: mensaje que viaja
  // entre el `Intermediary` y `UserHandler` indicando que la autenticación
  // fue exitosa. Incluye permisos, nombres y apellidos de usuario.
  MessageType message_type;
  NodeType source_node;
  char name[33];
  char last_name[33];
  uint8_t permissions;
  // Tamaño: 71 bytes
};

//TODO: completar.

// Datagramas entre `Intermediary`y `UserHandler`:
// >> De intermediario a al `UserHandler`:
/*
struct AuthenticationRequestUI {
  // Mensaje de consulta de autenticación: mensaje que el intermediario
  // redirige al `UserHandler` con los datos del mensaje 
  // `AuthenticationRequestCI` para realizar el proceso de autenticación. 
  MessageType message_type;
  NodeType source_node;
  char username[33];
  char hash[65];
  uint16_t client_identification;
  // Tamaño: 102 bytes
}; */

// >> Del `UserHandler` al intermediario 
/*
struct AuthenticationSuccessIU {
  // Mensaje de confirmación afirmativa de autenticación: mensaje que viaja
  // entre el `Intermediary` y `UserHandler` indicando que la autenticación
  // fue exitosa. Incluye permisos, nombres y apellidos de usuario.
  MessageType message_type;
  NodeType source_node;
  char name[33];
  char last_name[33];
  uint8_t permissions; 
  uint16_t client_identification;
  // Tamaño: 71 bytes
};

struct AuthenticationFailureIU {
  // Mensaje de confirmación negativa de autenticación: mensaje que viaja entre
  // el `Intermediary` y `UserHandler` indicando que la autenticación no fue
  // exitosa.
  MessageType message_type;
  NodeType source_node;
  uint8_t error;
  // Tamaño: 3 bytes
};
*/

// TODO: completar todos los datagramas pendientes. 
// Datagramas entre `Intermediary`y `DataCollector`:
// Datagramas entre `Intermediary` y `Backup_server`:
// Datagramas entre `DataCollector` e `Intel Galileo:
// Datagramas entre `Intel Galileo` y `ESP8266`:
// Datagramas entre `Backup_server` y `DataCollector` / `UserHandler`:

# endif