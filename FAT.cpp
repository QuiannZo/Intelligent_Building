#include "FAT.hpp"

#include <cstring>
#include <iostream>

// Constructor
FAT::FAT(/* args */) {
  for(int i = 0; i < FRAMES_TOTAL; ++i){
    strcpy(this->directory[i].fileName, "");
    this->directory[i].processId = 0;
    strcpy(this->directory[i].date, "");
  }

  strcpy(this->directory[24].fileName, "test.txt");
  this->directory[24].processId = 7;
  strcpy(this->directory[24].date, "24/03/2005");
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
  if (search(filename) == -1) {
    return false; 
  }

  int i = 0;
  while (directory[i].fileName[0] != '\0' && i < FRAMES_TOTAL) {
    i++;
  }
  if (i >= FRAMES_TOTAL) {
    return false;
  }
  // Copy name
  size_t strLength = std::strlen(filename);
  size_t copyLength = (strLength <= MAX_NAME_SIZE) ? strLength : MAX_NAME_SIZE; // TODO
  std::strncpy(directory[i].fileName, filename, copyLength);
  // Copy date
  strLength = std::strlen(date);
  copyLength = (strLength <= MAX_DATE_SIZE) ? strLength : MAX_DATE_SIZE; // TODO
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
bool FAT::write(char* filename, int processID, char* data) {
  int position = this->search(filename);
  std::cout << "*" << position << std::endl;
  if (position != -1) {
    if(this->open(filename, processID)) {
      if (this->directory[position].firstClusterAddress == -1) {
        int rChar = strlen(data);
        int frame = this->findEmptyFrame();
        this->directory[position].firstClusterAddress = frame;
        if(frame == -1) {
          return false;
        }
        int chrIndex = 0;
        bool continueWriting = true;
        while (continueWriting) {           
          if (rChar < FRAMES_TOTAL) {
            strcpy(&unit[frame * FRAME_SIZE], data);
          } else {
            strncpy(&unit[frame * FRAME_SIZE], data + chrIndex, FRAME_SIZE);
            chrIndex = chrIndex + FRAME_SIZE;
          }
          rChar = rChar - FRAMES_TOTAL;

          if(rChar > 0) {
            int newFrame = this->findEmptyFrame();
            fatTable[frame] = newFrame;
            frame = newFrame;
          } else { 
            continueWriting = false; 
          }
        }
      }
      else {
        //TODO, decidir que hacer cuando el archivo tiene datos
      }
      //this->close(filename, processID);
      return true;
    }
  }

  return false;
}

// Cambiarlo a while
int FAT::search(char *filename) {
  for (int i = 0; i < FRAMES_TOTAL; i++) {
    if (strcmp(this->directory[i].fileName, filename) == 0) {
      return i;
    }
  }
  return -1;
}

// -1 vacio
// -2 eofleName,
int FAT::findEmptyFrame() {
  for (int i = 0; i < FRAMES_TOTAL; i += FRAME_SIZE) {
    if (this->fatTable[i] == -1) {
      return i;
    }
  }
  return -1;
}

void FAT::deleteFrame() {}
std::cout << "Directory" << std::endl;
/*
LO que hace es ir al final, cursor pasa hasta el final, y escribe al final*/
void FAT::append() {}

void FAT::rename() {}
void FAT::list() {
  // buscar en todo el directorio
}

void FAT::print(bool verbose) {
    // Imprimir el directorio
    std::cout << "Directory" << std::endl;
    for (int i = 0; i < FRAMES_TOTAL; i++) {
        if (verbose) {
            std::cout << "File " << i << ": ";
        }
        std::cout << this->directory[i].fileName << " " << this->directory[i].date << " " << this->directory[i].processId << std::endl;
    }

    std::cout << "Unit" << std::endl;
    std::cout << "Frame:";
    for (int i = 0; i < UNIT_SIZE; i++) {
        if (verbose) {
          std::cout << unit[i];
        }
        if(i%60 == 0){
          std::cout << std::endl;
          std::cout << "Frame: ";
        }
    }
    std::cout << std::endl;
    std::cout << "FAT" << std::endl;
    for (int i = 0; i < FRAMES_TOTAL; i++) {
        if (verbose) {
          std::cout << "pos: " << fatTable[i] << std::endl;
        }
    }
}
// Imprimir, directorio, indice y unidad

// HAY 2 BORRAR, UN BORRAR PROFUNDO: Borra del inice, del directorio, y además
// de la unidad. el no profundo, borra solo del directorio..c_str