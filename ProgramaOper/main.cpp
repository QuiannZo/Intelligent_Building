#include "Threads.cpp"

int main() {
  // Crear los hilos
  std::thread writer_thread(writer);
  std::thread reader_thread(reader);

  // Esperar a que terminen
  writer_thread.join();
  reader_thread.join();

  return 0;
}