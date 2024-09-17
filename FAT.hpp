#include <iostream>
#include <cstring>

#ifndef FAT_HPP
#define FAT_HPP

struct directoryEntry {
    char fileName[30];
    short int firstClusterAddress;
    char date[10]; // puede ser un INT, NOTA DEL PROFE: TODO ESTATICO
    bool opened =  false;
    int processId;   
    //short int permissions;
};


class FAT {
private:
    // Attributes 
    // char unit[4096];// = {0};
    // NOTE: the cluster size is 8 chars, so the frame count is 4096/8 = 512.
    // We use `-1` to indicate an empty cluster and `-2` to indicate `end of file`.
    
    
    // short int fatTable[512] = {-1}; // short int: from -32,768 to 32,767.
    
    // Directory
    
    directoryEntry directory[512];

public:
    FAT(/* args */);
    ~FAT();
    // Methods
    bool open(char *fileName, int processId);
    bool close(char *filename, int processId);
    bool create(char* filename, char* date);
    void read();
    void write();
    int search(char* filename);
    void deleteFrame();
    void append();
    void rename();
    void list();
    void print();
   // Hacer RENAMEFILE?
};

#endif