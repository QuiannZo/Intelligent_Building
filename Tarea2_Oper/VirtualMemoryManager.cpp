#include "VirtualMemoryManager.hpp"

VirtualMemoryManager::VirtualMemoryManager(/* args */){
    // -1 significa que la página no está cargada en memoria.
    for(size_t i = 0; i < NUM_PAGES; ++i) {
        this->pageTable[i] = -1;
    }

    // Crear el archivo binario, que sería el almacenamiento secundario.
    this->createBinaryFile();

    // Se inicializan los marcos libres, al principio están todos libres.
    for (int i = NUM_FRAMES-1; i >= 0; --i) {
        freeFrameList.push_back(i); 
    }

    this->faultPages = 0;
    this->totalPages = 0;
}

VirtualMemoryManager::~VirtualMemoryManager(){ }

vector<int> VirtualMemoryManager::CalcPageOffset(int32_t logicalAddress) {
    // El primero es el número de página y el segundo es el offset.
    vector<int> PageOffset = {0, 0};
    int pageNumber = (logicalAddress >> 8) & 0xFF;
    int offset = logicalAddress & 0xFF;
    PageOffset[0] = pageNumber;
    PageOffset[1] = offset;

    return PageOffset;
}

int32_t VirtualMemoryManager::getPageValue(int32_t num) {
    return this->pageTable[num];
}

void VirtualMemoryManager::createBinaryFile() {
    const char* binaryFileName = "BACKING_STORE.bin";
  
    std::ofstream binaryOut(binaryFileName, std::ios::binary);
 
    if (!binaryOut) {
        std::cerr << "Error: no se pudo abrir el archivo" << std::endl;
        return;
    }

    for (int page = 0; page < NUM_PAGES; ++page) {
        for (int byte = 0; byte < PAGE_SIZE; ++byte) {
            // Se rellena con números.
            unsigned char value = static_cast<unsigned char>(page * PAGE_SIZE + byte);
            binaryOut.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }

    binaryOut.close();
    
    std::cout << "El archivo binario se creo con exito" << std::endl;
}

void VirtualMemoryManager::verifyPage(int32_t pageNum) {
    // En caso de que no queden marcos.
    if (freeFrameList.empty()) {
        cerr << "Error: No hay marcos libres disponibles" << std::endl;
        return; 
    }

    FILE *backingStore = fopen("BACKING_STORE.bin", "rb"); 
    
    // Si la página no está cargada en memoria física.
    if (this->pageTable[pageNum] == -1) { 
        // Se obtiene el marco libre.
        int freeFrame = freeFrameList.back();
        freeFrameList.pop_back();

        // Se busca en el almacenamiento secundario y se pone en un frame libre de la memoria física.
        fseek(backingStore, pageNum * 256, SEEK_SET); 
        fread(reinterpret_cast<void*>(&this->physicalMemory[freeFrame * FRAME_SIZE]), sizeof(char), 256, backingStore);
        
        // Se le agrega un valor a la tabla de páginas, para indicar que ya está cargada.
        this->pageTable[pageNum] = freeFrame;

        // Sumar los fallos de páginas.
        ++this->faultPages;
    }

    fclose(backingStore);

    // Llevar conteo de páginas
    ++this->totalPages;
}

void VirtualMemoryManager::readPhysicalMemory(int32_t pageNum) {
    for (int i = (pageNum*FRAME_SIZE); i < (pageNum*FRAME_SIZE)+FRAME_SIZE; ++i) {
        std::cout << static_cast<int>(static_cast<unsigned char>(this->physicalMemory[i])) << " ";
    }
    std::cout << std::endl;
}

int32_t VirtualMemoryManager::calcPhysicalAddress(int32_t pageNum, int32_t offset) {
    return this->pageTable[pageNum]*FRAME_SIZE+offset;
}

char VirtualMemoryManager::getPhysicalAddressValue(int32_t address) {
    return this->physicalMemory[address];
}
