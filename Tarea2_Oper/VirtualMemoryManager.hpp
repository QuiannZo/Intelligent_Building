#ifndef VIRTUALMEMORYMANAGER_HPP
#define VIRTUALMEMORYMANAGER_HPP

#include <vector>
#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

class VirtualMemoryManager {
private:
    // Para la memoria virtual.
    static const int PAGE_SIZE = 256;
    static const int NUM_PAGES = 256;

    // Para la memoria física.
    static const int FRAME_SIZE = 256;
    static const int NUM_FRAMES = 256;
    
    int32_t pageTable[NUM_PAGES]; 
    char physicalMemory[FRAME_SIZE * NUM_FRAMES]; 

public:
    VirtualMemoryManager(/* args */);
    ~VirtualMemoryManager();

    // Calcular número de página y el offset.
    vector<int> CalcPageOffset(int32_t logicalAddress);

    // Creación de archivo binario, que representará el almacenamiento secundario.
    void createBinaryFile();

    // Obtener el valor de una página.
    int32_t getPageValue(int32_t num);
    
};
#endif