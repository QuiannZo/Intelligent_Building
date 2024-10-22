
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std ;

// Abrir un archivo
string leerArchivo(string& pNombreArchivo) {
  ifstream archivo(pNombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error abriendo el archivo" << endl;
  }
  // para almacenar lo leído
  string linea;
  string contenidoTotal;
  while(getline(archivo,linea)) {
    contenidoTotal += linea + "\n";
  }
  archivo.close();
  return contenidoTotal;
}

int main(){
    int resultado=0 ;
    int s = 0,n = 0;
    char datos[256];
    char mensajeAutenticar[256];
    char guardar[256];
    struct sockaddr_in ipServidor;

    memset(datos, '0' ,sizeof(datos));
    memset(mensajeAutenticar, '0', sizeof(mensajeAutenticar));
    memset(guardar, '0' ,sizeof(guardar));

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

        char comando[256];
        cout << "Ingrese comando\n1.autenticar usuario contrasena\n2.crearArchivo nombreDeArchivo\n3. guardarArchivo nombreDeArchivo\n4. eliminarArchivo nombreDeArchivo\n5. abrirArchivo nombreDeArchivo" << std::endl;
        cin.getline(comando, sizeof(comando));
        
        // se copia el comando
        strncpy(mensajeAutenticar, comando, sizeof(mensajeAutenticar)-1);
        mensajeAutenticar[sizeof(mensajeAutenticar)-1] = '\0';
        
        // se envía al servidor
        write(s, mensajeAutenticar, strlen(mensajeAutenticar));
        memset(datos, 0, sizeof(datos));
        
        while((n = read(s, datos, sizeof(datos)-1)) > 0) {
          datos[n] = '\0';
          cout << endl << "Respuesta del servidor: " << datos << endl;
        }

        if(n < 0){
          cout << endl << "Error de lectura" << endl ;
        }
      }
    }

    return resultado;
}