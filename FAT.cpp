#include "FAT.hpp"

// Constructor
FAT::FAT(/* args */) {
  strcpy(this->directory[24].fileName, "test.txt");
  this->directory[24].processId = 7;
}

// Destructor
FAT::~FAT() {
  // poner destructor
}

// ir a buscar el directorio, si existe, y marcarlo como abierto.
// es una bandera, nada más
// para el que tiene escribir, tiene que decir que está abierto, porque solo
// ese proceso puede modificarlo. el abrir tiene guardado que proceso lo abrió
bool FAT::open(char *filename, int processId) {
  short int fileIndex = this->search(filename);
  if (fileIndex != -1) {
    if (directory[fileIndex].opened == true) {
      return false;
    }
    directory[fileIndex].opened = true;
    directory[fileIndex].processId = processId; // TODO_
    return true;
  }
  return false;
}
bool FAT::close(char *filename, int processId) {
  int fileIndex = this->search(filename);
  if (fileIndex != -1) {
    if (directory[fileIndex].opened == true &&
        directory[fileIndex].processId == processId) {
      directory[fileIndex].opened = false;
      return true;
    }
  }
  return false;
}

// agregar ene le directorio el nombre
// asignar el espacio en la primera unidad
bool FAT::create(char *filename, char *date) {
  int i = 0;
  while (directory[i].fileName[0] != '\0' && i < 512) {
    i++;
  }
  if (i >= 512) {
    return false;
  }
  // Copy name
  size_t strLength = std::strlen(filename);
  size_t copyLength = (strLength <= 30) ? strLength : 30; // TODO
  std::strncpy(directory[i].fileName, filename, copyLength);
  // Copy date
  strLength = std::strlen(date);
  copyLength = (strLength <= 10) ? strLength : 10; // TODO
  std::strncpy(directory[i].date, date, copyLength);
  return true;
}

/*
Leer: Lo que quiero que tengan, es un cursor implementado
Tener un leer quantum, quiero poder leer 10 bytes, 50, etc
En el proyecto NO siempre tenemos que leert desde el inicio del archivo, por
ejemplo desde el 3°. Y ese parametro de quantum, es un int. SI siempre leemos
desde el inicio, podemos perder el tiempo. ¿Dónde va ese cursor? EN el
directorio.

DE hecho con el cursor ya no tendriamos que guardar si está abierto o no.
El cursor es un int

*/
void FAT::read() {}

/*
Tiene que recibir el nombre del archivo y el dato.
EN c++ por facilidad, puede recibir la longitud, de que podemos elegir si la
tomamos de la estructura o la longitud del dato. NOSOTROS podemos decidir: SI
vamos a escribir a partir de ahí, si desplazan o aplazan El profe escogería:
reemplazar

Por conveniencia puedo escribir y que también tenga un cursor
*/
void FAT::write() {}

// Cambiarlo a while
int FAT::search(char *filename) {
  for (int i = 0; i < 512; i += 8) {
    if (strcmp(this->directory[i].fileName, filename) == 0) {
      return i;
    }
  }
  return -1;
}

void FAT::deleteFrame() {}

/*
LO que hace es ir al final, cursor pasa hasta el final, y escribe al final*/
void FAT::append() {}

void FAT::rename() {}
void FAT::list() {
  // buscar en todo el directorio
}

void FAT::print() {
  // imprimir el directorio
}
// Imprimir, directorio, indice y unidad

// HAY 2 BORRAR, UN BORRAR PROFUNDO: Borra del inice, del directorio, y además
// de la unidad. el no profundo, borra solo del directorio..c_str