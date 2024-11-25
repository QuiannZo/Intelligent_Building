
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>

#include "utilities.hpp"

using namespace std ;

// Datagramas generales:
struct Request {
  // Mensaje con el que responde un nodo cuando no puede manejar una datagrama
  // recibido previamente. 
  MessageType message_type;
  NodeType source_node;
  int value;
};

int main(){
    int resultado 0;
    int s = 0
    char mensaje[256];
    struct sockaddr_in ipServidor;

    memset(mensaje, '0', sizeof(mensaje));

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
        for(int i = 0; i < 100; ++1){
          message.message_type = kRequest;
          message.source_node = kTest;
          message.value = index;
        }
        
        write(s, mensaje, strlen(mensaje));

        close(s);
      
      }
    }

    return resultado;
}