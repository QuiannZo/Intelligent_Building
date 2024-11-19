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

std::queue<std::string> message_queue;
std::mutex mtx;
std::condition_variable cv;
bool finish = false;

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
  kInvalidRequest,
  kCommunicationError,
  kUnknownError,
  kLongFileHeader, 
  kTransmissionError,
};

// Datagramas generales:
struct InvalidRequest {
  // Mensaje con el que responde un nodo cuando no puede manejar una datagrama
  // recibido previamente. 
  MessageType message_type;
  NodeType source_node;
};


void writer() {
    for (int i = 1; i <= 10; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula trabajo
      std::string message = "Mensaje " + std::to_string(i);

      // Bloquea y agrega un mensaje a la cola
      {
        std::lock_guard<std::mutex> lock(mtx);
        message_queue.push(message);
      }

      // Notifica al lector
      cv.notify_one();
      std::cout << "[Writer] Enviado: " << message << std::endl;
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
      std::string message = message_queue.front();
      message_queue.pop();
      std::cout << "[Reader] Recibido: " << message << std::endl;
    }

    // Si el escritor termina y la cola esta vaci­a, sale del bucle
    if (finish && message_queue.empty()) {
      break;
    }
  }
}
