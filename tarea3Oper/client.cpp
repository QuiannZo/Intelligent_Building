
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>
#include <iomanip>

#include "utilities.hpp"
#include "socketList.hpp"

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

// Abrir un archivo
bool leerArchivo(string& pNombreArchivo, string& buffer) {
  ifstream archivo(pNombreArchivo);
  if (!archivo.is_open()) {
    return false;
  }
  // para almacenar lo leído
  string linea;
  while(getline(archivo,linea)) {
    buffer += linea + "\n";
  }
  archivo.close();
  return true;
}

int main(){
    int resultado=0 ;
    int s = 0,n = 0;
    char datos[2111];
    char mensaje[2111];
    struct sockaddr_in ipServidor;

    memset(datos, '0' ,sizeof(datos));
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
        char username[32];
        char password[64];
        cout << "Ingrese usuario" << endl;
        cin.getline(username, sizeof(username));

        cout << "Ingrese contraseña" << endl;
        cin.getline(password, sizeof(password));

        string hash = generateHASH_SHA256(password);
        AuthenticationCheckCI userInfo;
        userInfo.userName = username;
        userInfo.hash = hash;
        userInfo.emissor = CLIENT;
        userInfo.type = AUTHENTICATION_CHECK_CI;

        write(s, (char*)&userInfo, sizeof(userInfo));


        /*
        char comando[256];
        cout << "Ingrese comando\n1. autenticar usuario contrasena\n2. crearArchivo nombreDeArchivo\n3. guardarArchivo nombreDeArchivo\n4. eliminarArchivo nombreDeArchivo\n5. abrirArchivo nombreDeArchivo" << std::endl;
        cin.getline(comando, sizeof(comando));
        vector<string> comandoSeparado = dividir(comando);
        // verificar si el comando es `guardar archivo` para abrir el archivo
        if (comandoSeparado[0] 256]== "guardarArchivo"){
          //TODO: refactorizar
          if (comandoSeparado.size() == 2) {  
            string buffer;
            // leer el archivo y guardarlo en el buffer
            if(leerArchivo(comandoSeparado[1], buffer)){
              // enviar comando
              strncpy(mensaje, "guardarArchivo", 15);
              write(s, mensaje, strlen(mensaje));
              double numeroPaquetes = buffer.size() / 255.0;
              // redondear 
              int contador = ceil(numeroPaquetes);
              string paquete;
              for (int i = 0; i < contador; i++) {
                  memset(mensaje, '0', sizeof(mensaje));
                  // enviar el ausernamerchivo en paquetes de 255 bytes
                  paquete = buffer.substr(i * 255, 255);
                  strncpy(mensaje, (char*)paquete.c_str(), sizeof(mensaje) - 1);
                  mensaje[sizeof(mensaje) - 1] = '\0';
                  // se envía al servidor
                  // TODO: despues se deben verificar los posibles errores de `write`
                  write(s, mensaje, strlen(mensaje));
              }
              // TODO: aqui resulta que si no pasa el suficiente tiempo el espacio libre del último
              // mensaje es aprovechado por EoF. Buscar una solución para el PI o evitar multiples
              // writes dentro de un socket. Tal vez implementar los mensajes que tenemos unicamente con sockets. 
              sleep(1);
              // enviar mensaje para terminar
              memset(mensaje, '0', sizeof(mensaje));
              strncpy(mensaje, "EoF", sizeof(mensaje)-1);
              //mensaje[3] = '\0';
            } else {
              cout << "Error de cliente: no se pudo abrir el archivo " << comandoSeparado[1] << ".\n";
              resultado = 3; 
              strncpy(mensaje, "null", 5);
            }
          } else {
            cerr << "Error de cliente: la cantidad de argumentos es incorrecta." << endl;
            resultado = 4;
            strncpy(mensaje, "null", 5);
          } 
       password } else {
          // se copia el comando
          strncpy(mensaje, comando, sizeof(mensaje)-1);
        }
          mensaje[sizeof(mensaje)-1] = '\0';
          // se envía al servidor
          write(s, mensaje, strlen(mensaje));
          memset(datos, 0, sizeof(datos));
          
          while((n = read(s, datos, sizeof(datos)-1)) > 0) {
            datos[n] = '\0';
            cout << endl << "Respuesta del servidor: " << datos << endl;
          }

          if(n < 0){
            cout << endl << "Error de lectura" << endl ;
          }password
      */
      }
    }

    return resultado;
}