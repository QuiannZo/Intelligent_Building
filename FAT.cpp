#include "FAT.hpp"

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

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
    resetCursors(fileIndex);
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
bool FAT::read(char* filename, char* buffer, int processID, int nChar) {
  //char* buffer[nChar + 1];
  int directoryPos = this->search(filename);
  if (directoryPos != -1) {
    if(directory[directoryPos].opened == true && directory[directoryPos].processId == processID) {
      int count = 0;
      int chrToCopy;
      // when copy an incomplete initial frame
      if (this->directory[directoryPos].charCursor != 0){
        chrToCopy = FRAME_SIZE - this->directory[directoryPos].charCursor - 1;
        std::strncpy(buffer, &this->unit[this->directory[directoryPos].firstFrameAddress], chrToCopy);
        count = chrToCopy;
        if (chrToCopy < nChar) {
          // Update cursors
          this->directory[directoryPos].charCursor = 0;
          this->directory[directoryPos].frameCursor = 
            this->fatTable[this->directory[directoryPos].frameCursor];
        } else {
          // all chrs were copied
          this->directory[directoryPos].charCursor +=  chrToCopy;
        }
      }
      while(count < nChar) {
        chrToCopy = std::min(FRAME_SIZE, nChar - count);
        std::strncpy(buffer + count, &this->unit[this->directory[directoryPos].frameCursor * FRAME_SIZE], chrToCopy);
        count += chrToCopy;
        if (chrToCopy == FRAME_SIZE) {
          // update the frame cursor
          this->directory[directoryPos].frameCursor = 
            this->fatTable[this->directory[directoryPos].frameCursor];
        } else {
          // update the chr cursor 
          this->directory[directoryPos].charCursor +=  chrToCopy;
        }
      }
      buffer[count] = '\0';
      return true;
    }
    strcpy(buffer,(char*)"Error: File is not opened");
  }
  strcpy(buffer,(char*)"Error: Could not find file");
  return false;
}

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
    // the file is empty
    if(directory[position].opened == true && directory[position].processId == processID) {
      if (this->directory[position].firstFrameAddress == -1) {
        int firstFrame = findEmptyFrame();
        if (firstFrame == -1) {
          return false;
        }
        this->directory[position].firstFrameAddress = firstFrame;
        this->fatTable[position] = -2; // indicates the EoF
        // Update the cursor
        this->resetCursors(firstFrame);
        return writeUnit(data, firstFrame, true);
      } else {
        // over-write the file
        deleteFromPosition(position);
        int firstFrame = this->directory[position].firstFrameAddress;
        this->fatTable[firstFrame] = -2; // indicates the EoF
        return writeUnit(data, firstFrame, true);
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

bool FAT::searchCredentials(char *username, char *hash) {
  char *foundUsername = strstr(this->unit + 0, username);
  char *foundHash = strstr(this->unit + 0, hash);

  if(foundHash != NULL && foundUsername != NULL){
    return true;
  } 
  return false;
}

bool FAT::loadFile(char *filename, int processID) {
    // open the file
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open the file " << filename << std::endl;
        return false;
    }

    // Get the current time
    time_t current_time = time(0);
    struct tm tmStruct;
    char* date = new char[11]; // "dd/mm/yyyy\0"
    // Convert time_t to tm struct
    localtime_r(&current_time, &tmStruct);
    // Format the date as dd/mm/yyyy
    strftime(date, 11, "%d/%m/%Y", &tmStruct);

    // create the file in our file system
    if (!this->create(filename, date) || !this->open(filename, processID)) {
      return false;
    }
    // read all file using a <stringstream>
    std::stringstream buffer;
    buffer << file.rdbuf();

    // store the file in the file system
    this->append(filename, processID, const_cast<char*>(buffer.str().c_str()));

    // close the files
    file.close();
    this->close(filename, processID);
    return false;
}

bool FAT::saveFile(char *filename, int processID, char* writingName) {
  int directoryPos = this->search(filename);
  if (directoryPos != -1) {
    if(directory[directoryPos].opened == true && directory[directoryPos].processId == processID) {
      // Open the file
    std::ofstream outFile(writingName); // create or overwrite

    // verify if it was opened successfully
    if (!outFile) {
        std::cerr << "Error: Failed to open the file " << writingName << std::endl;
        return false;
    }
      
    char buffer[FRAME_SIZE + 1];
    bool stop = false;
    int frameCursor = directoryPos;

    while (!stop) {
      //TODO: Probar que el archivo funcione bien con archivos formados por más de un frame. 
      std::strncpy(buffer, &this->unit[frameCursor*FRAME_SIZE], FRAME_SIZE);
      outFile << buffer; 
      frameCursor = this->fatTable[frameCursor];
      if (frameCursor == -2) {
        stop = true;
      }
    } 
    // Close the file
    outFile.close();
    return true;
    }   
  }
  return false;
}

bool FAT::deleteFrame(int position) {
  if (position < FRAMES_TOTAL) {
    for (int i = 0; i < FRAME_SIZE; i++) {
      this->unit[position * FRAME_SIZE + i] = '\0';
    }
    return true;
  }
  return false;
}

bool FAT::deleteFromPosition(int firstFrame) {
  int currentFrame = firstFrame;
  int nextFrame = this->fatTable[currentFrame];
  bool repeat = true;
  // while EoF is not found
  while (repeat) {
    if (nextFrame == -1) {
      // the FAT table has an error
      return false;
    }
    // hard delete
    if (!deleteFrame(currentFrame)) {
      return false;
    }
    this->fatTable[currentFrame] = -1;
    if (nextFrame == -2) {
      repeat = false;
    } else {
      currentFrame = nextFrame;
      nextFrame = this->fatTable[currentFrame];
    }
  }
  return true;
}

bool FAT::writeUnit(char *data, int startFrame, bool fromFirstPos) {
  // NOTE: in the next line, 1 is added to consider `\0`, for this reason all *char 
  // received as argument must have the final '\0'
   int remainingChars = std::strlen(data) + 1;
   int dataIndex = 0;
   bool continueWriting = true;
   int newFrame = -1;
  // when the frame has some data, we do not start writing from the beginning. 
  if (!fromFirstPos) {
    int firstPos = 0;
    // Find last position
    bool cont = true; 
    while(cont && firstPos < FRAME_SIZE) {
      if (this->unit[startFrame * FRAME_SIZE + firstPos] == '\0') {
        cont = false;
      } else {
        firstPos++;
      }
    }
    // copy to the remaining space in the frame 
    int charsToCopy = FRAME_SIZE - firstPos;
    // Note that 0 chars can be copied if the frame is full 
    std::strncpy(&unit[startFrame * FRAME_SIZE + firstPos], data + dataIndex, charsToCopy);
    remainingChars -= charsToCopy;
    dataIndex += charsToCopy;
    if (remainingChars > 0) {
      newFrame = this->findEmptyFrame();
      if(newFrame == -1) {
        return false;
      }
      fatTable[startFrame] = newFrame;
      startFrame = newFrame;
    } else {
      fatTable[startFrame] = -2;
      continueWriting = false;
    }
  }
  // write the remaining data starting from a new frame
  while (continueWriting) {  
    if (remainingChars < FRAME_SIZE) {
      strncpy(&unit[startFrame * FRAME_SIZE], data + dataIndex, remainingChars);
    } else {
      strncpy(&unit[startFrame * FRAME_SIZE], data + dataIndex, FRAME_SIZE);
      dataIndex += FRAME_SIZE;
    }
    remainingChars -= FRAME_SIZE;
    if(remainingChars > 0) {
      newFrame = this->findEmptyFrame();
      if(newFrame == -1) {
        return false;
      }
      fatTable[startFrame] = newFrame;
      startFrame = newFrame;
    } else { 
      continueWriting = false; 
    }
    fatTable[startFrame] = -2; // indicates the EoF in the FT
  }
  return true;
}

//
int FAT::findFinalFrame(int firstFrame) {
  int currentFrame = firstFrame;
  int nextFrame = this->fatTable[currentFrame];
  // while EoF is not found
  while (nextFrame != -2) {
    if (nextFrame == -1) {
      // the Fat table has an error
      return -1;
    }
    currentFrame = nextFrame;
    nextFrame = this->fatTable[currentFrame];
  }
  return currentFrame;
}

// 
bool FAT::resetCursors(int directoryPosition) {
  this->directory[directoryPosition].frameCursor = this->directory[directoryPosition].firstFrameAddress;
  this->directory[directoryPosition].charCursor = 0;
  return false;
}

// -1 empty
// -2 EoF
int FAT::findEmptyFrame() {
  for (int i = 0; i < FRAMES_TOTAL; i += 1) {
    if (this->fatTable[i] == -1) {
      return i;
    }
  }
  return -1;
}

bool FAT::append(char* filename, int processID, char* data) {
  int position = this->search(filename);
  if (position != -1) {
    if(directory[position].opened == true && directory[position].processId == processID) {
      // when the file is empty
      if(this->directory[position].firstFrameAddress == -1) {
        int firstFrame = findEmptyFrame();
        if (firstFrame == -1) {
          return false;
        }
        this->directory[position].firstFrameAddress = firstFrame;
        this->fatTable[position] = -2; // indicates the EoF
        this->resetCursors(firstFrame);
        return writeUnit(data, firstFrame, true);
      } else {
         // when the file has data, the last frame must be found
        int lastFrame = findFinalFrame(position);
        if (lastFrame == -1) {
          return false;
        }
        return writeUnit(data, lastFrame, false);
      }
    }
  }
  return false;
}

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
        std::cout << this->directory[i].fileName << " " << this->directory[i].date << " FT->" << this->directory[i].firstFrameAddress << std::endl;
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

bool FAT::deleteFile(char *filename, int processID) {
  int position = this->search(filename);
  if (position == -1) {
    return false;
  }
  if(directory[position].opened == true && directory[position].processId == processID) {
    if (!deleteFromPosition(position)) {
      return false;
    }
    this->directory[position].fileName[0] = '\0';
    this->directory[position].date[0] = '\0';
    this->directory[position].processId = -1;
    this->directory[position].firstFrameAddress = -1;
    this->directory[position].opened = false;
  }
  return true;
}
// Imprimir, directorio, indice y unidad

// HAY 2 BORRAR, UN BORRAR PROFUNDO: Borra del inice, del directorio, y además
// de la unidad. el no profundo, borra solo del directorio..c_str