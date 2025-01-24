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

string generateHASH_SHA256(const string& password) {
    // See: https://stackoverflow.com/questions/918676/generate-sha-hash-in-c-using-openssl-library
    // https://docs.openssl.org/master/man3/SHA256_Init/

    unsigned char hash[SHA256_DIGEST_LENGTH]; // sha256 has a length of 32 bits
    // Cast the string to a unsigned char*
    const unsigned char* data = (const unsigned char*)password.c_str(); // cast
    SHA256(data, password.size(), hash); // get the sha256 hash
    stringstream ss;
    // convert to hexadecimal
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// autenticar el cliente
bool autenticar(const vector<string>& parametros) {
    if (parametros.size() != 3) {
      return false;
    }
    if (parametros[0] != "autenticar") {
      return false;
    }

    string usuario = parametros[1];
    string password = parametros[2];
    string hash = generateHASH_SHA256(password);
    
    ifstream file("usersData.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        string fileUsername, fileHash;

        getline(iss, fileUsername, ',');
        getline(iss, fileHash, ',');

        // Se verificar el usuario y contraseña
        if (usuario == fileUsername && hash == fileHash) {
          return true; 
        }
    }
    return false;  
}

bool crearArchivo(const vector<string>& parametros){
  cout << "Comando identificado como: crearArchivo";
  return true;
}

bool guardarArchivo(char* mensajeRecibido, int conexion){
  string archivo(mensajeRecibido);
  while(true) {
    memset(mensajeRecibido, '\0', 256);
    int bytesLeidos = read(conexion, mensajeRecibido, 255);

    if (bytesLeidos <= 0) {
        break; // sucedió un error en la lectura
    }
    // si es diferente al fin del archivo
    if (strncmp(mensajeRecibido, (char*)"EoF", 3) != 0) {
        archivo.append(mensajeRecibido);
    } else {
        break; // final del
    } 
  }
  // Imprimir el archivo
  cout << "El archivo guardado es: \n";
  cout << archivo;
  return true;
}

bool eliminarArchivo(const vector<string>& parametros){
  cout << "Comando identificado como: eliminarArchivo";
  return true;
}



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
      cout << " IP Remoto: " << strIpRemoto << endl ;
      cout << "Se ingresó comando: " << comandoSeparado[0] << endl;
      
      bool verificarAutenticacion;
      bool mode;
      string respuesta;
      if(comandoSeparado[0] == "autenticar") {
        verificarAutenticacion = autenticar(comandoSeparado);
        // se envía la respuesta al cliente
        if(verificarAutenticacion) {
          respuesta = "verdadero";
        } else {
          respuesta = "falso";
        }
      } else if (comandoSeparado[0] == "crearArchivo") {
        mode = crearArchivo(comandoSeparado);
        respuesta = "Comando identificado como: crearArchivo";
      } else if (comandoSeparado[0] == "guardarArchivo") {
        mode = guardarArchivo(mensajeRecibido, conexion);
        respuesta = "Archivo guardado exitosamente";
      } else if (comandoSeparado[0] == "eliminarArchivo") {
        mode = eliminarArchivo(comandoSeparado);
        respuesta = "Comando identificado como: eliminarArchivo";
      } else {
        respuesta = "debe ingresar comando válido";
      }
      send(conexion, (char*)respuesta.c_str(), respuesta.size(), 0);
      close(conexion);
    }
    sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;

  return 0;

}