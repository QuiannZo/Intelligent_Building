#ifndef VIRTUALMEMORYMANAGER_HPP
#define VIRTUALMEMORYMANAGER_HPP

#include <vector>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <unordered_map>
#include <queue>

using namespace std;

class VirtualMemoryManager {
private:
    // Para la memoria virtual.
    static const int PAGE_SIZE = 256;
    static const int NUM_PAGES = 256;

    // Para la memoria física.
    static const int FRAME_SIZE = 256;
    static const int NUM_FRAMES = 128;
    
    // Tabla de páginas y la memoria física.
    int32_t pageTable[NUM_PAGES]; 
    char physicalMemory[FRAME_SIZE * NUM_FRAMES]; 
    
    // Estos son los marcos libres
    std::vector<int> freeFrameList;

    // Variables para estadísticas de fallos de páginas
    int totalPages;
    int faultPages;

    // Para realizar FIFO en el reemplazo de página
    unordered_map<int, int> pageFrameMap; // Mapa de páginas a marcos
    queue<int> frameQueue; // Cola FIFO de marcos

public:
    VirtualMemoryManager(/* args */);
    ~VirtualMemoryManager();

    // Calcular número de página y el offset.
    vector<int> CalcPageOffset(int32_t logicalAddress);

    // Creación de archivo binario, que representará el almacenamiento secundario.
    void createBinaryFile();

    // Obtener el valor de una página.
    int32_t getPageValue(int32_t num);
    
    // Se le pasa como argumento el número de página, para buscar si está en la memoria física.
    void verifyPage(int32_t pageNum);

    // Para leer el contenido de la memoria física.
    void readPhysicalMemory(int32_t pageNum);
    
    // Calcular posición exacta en memoria física.
    int32_t calcPhysicalAddress(int32_t pageNum, int32_t offset);
    
    // Obtener el valor en la dirección física.
    char getPhysicalAddressValue(int32_t address);

    // Obtener páginas consultadas.
    int getTotalPages(){ return this->totalPages;}

    // Obtener fallos de páginas.
    int getFaultPages(){ return this->faultPages;}
    
};
#endif