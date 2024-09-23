#include <iostream>
#include <cstring>

#ifndef FAT_HPP
#define FAT_HPP

const int MAX_NAME_SIZE = 30;
const int MAX_DATE_SIZE = 10;
const int FRAME_SIZE = 60; // TODO
const int UNIT_SIZE = 6000;
const int FRAMES_TOTAL = UNIT_SIZE/FRAME_SIZE;

struct directoryEntry {
    char fileName[MAX_NAME_SIZE + 1];
    int firstFrameAddress = -1;
    char date[MAX_DATE_SIZE + 1]; // puede ser un INT, NOTA DEL PROFE: TODO ESTATICO
    bool opened =  false;
    short int processId = -1;   
    //short int permissions;
};


class FAT {
private:
    // Attributes 
    char unit[UNIT_SIZE] = "";// = {0};
    // Fat table:
    // We use `-1` to indicate an empty cluster and `-2` to indicate `end of file`.
    short int fatTable[FRAMES_TOTAL]; // short int: from -32,768 to 32,767.
    // Directory
    directoryEntry directory[FRAMES_TOTAL];
    // Private methods
    bool deleteFrame(int position); // position from 0 to UNIT_SIZE - 1
    bool deleteFromPosition(int firstFrame);
    bool writeUnit(char* data, int startFrame, bool fromFirstPos);
    int findFinalFrame(int firstFrame);

public:
    FAT(/* args */);
    ~FAT();
    // Methods
    bool open(char *fileName, int processId);
    bool close(char *filename, int processId);
    bool create(char* filename, char* date);
    void read();
    bool write(char* filename, int processID, char* data);
    int search(char* filename);
    bool append(char* filename, int processID, char* data);
    bool rename(char* filename, char* newFilename);
    void list(); // list files in directory
    void print(bool verbose = false);
    bool deleteFile(char* filename, int processID);
    int findEmptyFrame();
    bool searchCredentials(char *username, char *hash);
};

#endif