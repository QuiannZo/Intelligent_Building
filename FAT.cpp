#include "FAT.hpp"

#include <cstring>
#include <iostream>

// Constructor
FAT::FAT(/* args */) {
  // Init fat table 
  for (size_t i = 0; i < FRAMES_TOTAL; i++) {
    fatTable[i] = -1;
  }
  // Init directory
  for(int i = 0; i < FRAMES_TOTAL; ++i){
    this->directory[i].fileName[0] = '\0';
    this->directory[i].date[0] = '\0';
  }
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
  if (search(filename) > -1) {
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
  if (strLength < MAX_NAME_SIZE) {
     std::strncpy(directory[i].fileName, filename, strLength);
     directory[i].fileName[strLength] = '\0';
  } else {
    std::strncpy(directory[i].fileName, filename, MAX_NAME_SIZE);
    directory[i].fileName[MAX_NAME_SIZE] = '\0';
  }
  // Copy date
  strLength = std::strlen(date);
  if (strLength < MAX_DATE_SIZE) {
     std::strncpy(directory[i].date, date, strLength);
     directory[i].date[strLength] = '\0';
  } else {
    std::strncpy(directory[i].date, date, MAX_DATE_SIZE);
    directory[i].date[MAX_DATE_SIZE] = '\0';
  }
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
  if (position != -1) {
    if(directory[position].opened == true && directory[position].processId == processID) {
      if (this->directory[position].firstClusterAddress == -1) {
        int remainingChars = std::strlen(data);
        int frame = this->findEmptyFrame();
        fatTable[frame] = -2; // indicates the EoF in the FT   
        this->directory[position].firstClusterAddress = frame;
        if(frame == -1) {
          return false;
        }
        int chrIndex = 0;
        bool continueWriting = true;
        while (continueWriting) {  
          if (remainingChars < FRAME_SIZE) {
            //strcpy(&unit[frame * FRAME_SIZE], data + chrIndex);
            strncpy(&unit[frame * FRAME_SIZE], data + chrIndex, remainingChars);
          } else {
            strncpy(&unit[frame * FRAME_SIZE], data + chrIndex, FRAME_SIZE);
            chrIndex += FRAME_SIZE;
          }
          remainingChars -= FRAME_SIZE;

          if(remainingChars > 0) {
            int newFrame = this->findEmptyFrame();
            fatTable[frame] = newFrame;
            frame = newFrame;
            fatTable[frame] = -2; // indicates the EoF in the FT
          } else { 
            fatTable[frame] = -2; // indicates the EoF in the FT
            continueWriting = false; 
          }
        }
      }
      else {
        //TODO, decidir que hacer cuando el archivo tiene datos
      }
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
  for (int i = 0; i < FRAMES_TOTAL; i += 1) {
    if (this->fatTable[i] == -1) {
      return i;
    }
  }
  return -1;
}

void FAT::deleteFrame() {}
/*
LO que hace es ir al final, cursor pasa hasta el final, y escribe al final*/
void FAT::append() {}

bool FAT::rename(char* filename, char* newFilename) {
  int position = this->search(filename);
  if (position == -1) {
    return false;
  }
  // Copy name
  size_t strLength = std::strlen(newFilename);
  if (strLength < MAX_NAME_SIZE) {
     std::strncpy(directory[position].fileName, newFilename, strLength);
     directory[position].fileName[strLength] = '\0';
  } else {
    std::strncpy(directory[position].fileName, newFilename, MAX_NAME_SIZE);
    directory[position].fileName[MAX_NAME_SIZE] = '\0';
  }
  return true;
}

void FAT::list() {
  std::cout << "Directory files:" << std::endl;
  for (int i = 0; i < FRAMES_TOTAL; i++) {
    if (directory[i].fileName[0] != '\0') {
      std::cout << "\t\t" << directory[i].fileName << std::endl;
    }
  }
}

void FAT::print(bool verbose) {
    // Imprimir el directorio
    std::cout << "Directory" << std::endl;
    for (int i = 0; i < FRAMES_TOTAL; i++) {
        if (verbose) {
            std::cout << "File " << i << ": ";
        }
        std::cout << this->directory[i].fileName << " " << this->directory[i].date << " FT->" << this->directory[i].firstClusterAddress << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Unit" << std::endl;
    for (int i = 0; i < FRAMES_TOTAL; i++) {
      if (verbose) {
        std::cout << "Frame " << i << ": ";
      }
      for (int j = 0; j < FRAME_SIZE; j++) {
        std::cout << unit[i*FRAME_SIZE + j];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "FAT Table" << std::endl;
    for (int i = 0; i < FRAMES_TOTAL; i++) {
      if (verbose) {
        std::cout << "FAT position " << i << ": ";
      }
        std::cout << fatTable[i] << std::endl;
    }
}
// Imprimir, directorio, indice y unidad

// HAY 2 BORRAR, UN BORRAR PROFUNDO: Borra del inice, del directorio, y además
// de la unidad. el no profundo, borra solo del directorio..c_str