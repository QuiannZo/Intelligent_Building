#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>
#include <cstdint>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;
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

std::queue<Request> message_queue;
std::mutex mtx;
std::condition_variable cv;
bool finish = false;


void receiver() {
  char datos[256]; 
  char mensajeRecibido[256];
	int socketServidor = 0, conexion = 0;
	struct sockaddr_in ip;
	socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketServidor < 0) {
    cout << "Error en la creación del socket" << endl;
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
      for(int i = 0; i < 100; ++i){
        memset(mensajeRecibido, 0, sizeof(mensajeRecibido));
        read(conexion, mensajeRecibido, sizeof(Request));
 
        Request message;
        memcpy(&message, mensajeRecibido, sizeof(Request));
        //cout << "Message value: " << message.value << endl;

          // Bloquea y agrega un mensaje a la cola
        {
          std::lock_guard<std::mutex> lock(mtx);
          message_queue.push(message);
        }

        // Notifica al lector
        cv.notify_one();
        std::cout << "[Receiver] Enviado: " << message.value << std::endl;
      
      }
     
      close(conexion);
      cout << endl << "[CONEXION CERRADA]" << endl;
      cout << "Presione Control C" << endl;

    }
  }
  // Señal para terminar
  {
    std::lock_guard<std::mutex> lock(mtx);
    finish = true;
  }
  cv.notify_one();


  cout << endl << "[SERVIDOR DETENIDO]" << endl;

}

// Funcion para el hilo lector
void processor() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return !message_queue.empty() || finish; }); // Espera hasta que haya mensajes o se indique que termina

    while (!message_queue.empty()) {
      Request message = message_queue.front();
      message_queue.pop();
      std::cout << "[Processor] Recibido: " << message.value << std::endl;
    }

    // Si el escritor termina y la cola esta vaci­a, sale del bucle
    if (finish && message_queue.empty()) {
      break;
    }
  }
}
