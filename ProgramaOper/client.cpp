
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>

using namespace std ;

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
  kRequest,
  kCommunicationError,
  kUnknownError,
  kLongFileHeader, 
  kTransmissionError,
};

// Datagramas generales:
struct Request {
  // Mensaje con el que responde un nodo cuando no puede manejar una datagrama
  // recibido previamente. 
  MessageType message_type;
  NodeType source_node;
  int value;
};

int main(){
    int resultado = 0;
    int s = 0;  char mensajeRecibido[256];
   
    struct sockaddr_in ipServidor;

    if((s = socket(AF_INET, SOCK_STREAM, 0))< 0){
      cout << "Error de creación de socket" << endl;
      resultado=1 ;
    } else {
      ipServidor.sin_family = AF_INET;
      ipServidor.sin_port = htons(1337);
      ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

      if(connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor))<0){
        cout << endl << "Error de conexión por IP o puerto" << endl ;
        resultado= 2;
      } else {
        Request message;
        message.message_type = kRequest;
        message.source_node = kTest;
        for(int i = 0; i < 100; ++i){
   
          message.value = i;

          write(s, reinterpret_cast<char *>(&message), sizeof(message));
          cout << "Mensaje enviado: " << i << endl;
        }

        close(s);
        cout << "Cliente finalizado" << endl;
      
      }
    }

    return resultado;
}