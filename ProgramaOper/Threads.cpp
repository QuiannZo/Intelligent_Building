#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>
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


void writer() {
    for (int index = 1; index <= 10; ++index) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula trabajo
      Request message;
      message.message_type = kRequest;
      message.source_node = kTest;
      message.value = index;

      // Bloquea y agrega un mensaje a la cola
      {
        std::lock_guard<std::mutex> lock(mtx);
        message_queue.push(message);
      }

      // Notifica al lector
      cv.notify_one();
      std::cout << "[Writer] Enviado: " << message.value << std::endl;
    }

    // Señal para terminar
    {
      std::lock_guard<std::mutex> lock(mtx);
      finish = true;
    }
    cv.notify_one();
}

// Funcion para el hilo lector
void reader() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return !message_queue.empty() || finish; }); // Espera hasta que haya mensajes o se indique que termina

    while (!message_queue.empty()) {
      Request message = message_queue.front();
      message_queue.pop();
      std::cout << "[Reader] Recibido: " << message.value << std::endl;
    }

    // Si el escritor termina y la cola esta vaci­a, sale del bucle
    if (finish && message_queue.empty()) {
      break;
    }
  }
}
