
#include <iostream>

#include <netdb.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

 

using namespace std ;


int main(){

    int resultado=0 ;

    int s = 0,n = 0;

    char datos[256];

    struct sockaddr_in ipServidor;

 

    memset(datos, '0' ,sizeof(datos));

 

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

        while((n = read(s, datos, sizeof(datos))) > 0){

          datos[n] = 0;

          cout << endl << string(datos) << endl ;

        }

 

        if( n < 0){

          cout << endl << "Error de lectura" << endl ;

        }

      }

    }

  

    return resultado;

}