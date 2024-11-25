#include <iostream>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <openssl/sha.h>
#include "utilities.hpp"

using namespace std ;



int main(){
	char datos[256]; 
  char mensajeRecibido[256];
	int socketServidor = 0, conexion = 0;
	struct sockaddr_in ip;
	socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketServidor < 0) {
    cout << "Error en la creación del socket" << endl;
    return 1;
  }

	memset(&ip, '0', sizeof(ip));
	memset(datos, '0', sizeof(datos));
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = htonl(INADDR_ANY);
	ip.sin_port = htons(1337);

  bind(socketServidor, (struct sockaddr*)&ip , sizeof(ip));
	listen(socketServidor , 20);

  int msjs =0 ;
  sleep(1);
  struct sockaddr_storage ipRemoto;
  socklen_t l= sizeof(ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;

  cout << endl << "[SERVIDOR ESCUCHANDO]" << endl ;

	while(msjs<5000){
		conexion= accept(socketServidor, (struct sockaddr*) &ipRemoto, &l);
    if (conexion!=-1) {
      
      // se recibe el comando del cliente
      memset(mensajeRecibido, 0, sizeof(mensajeRecibido));
      read(conexion, mensajeRecibido, sizeof(mensajeRecibido));
      
      // se divide en tokens
      const char* comando(mensajeRecibido);
      vector<string> comandoSeparado = dividir(comando);

      struct sockaddr_in *s = (struct sockaddr_in *)&ipRemoto;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);

      
      close(conexion);
    }
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;

  return 0;

}