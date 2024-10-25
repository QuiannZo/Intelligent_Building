#include "VirtualMemoryManager.hpp"

VirtualMemoryManager::VirtualMemoryManager(/* args */){
    // -1 significa que la página no está cargada en memoria.
    for(size_t i = 0; i < NUM_PAGES; ++i) {
        this->pageTable[i] = -1;
    }

    // Crear el archivo binario, que sería el almacenamiento secundario.
    this->createBinaryFile();
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
    
    std::cout << "El archivo binario se creó con éxito" << std::endl;
}
