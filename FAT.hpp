#include <iostream>
#include <cstdint>
#include <cstring>

#ifndef FAT_HPP
#define FAT_HPP


const int MAX_NAME_SIZE = 100;
const int MAX_DATE_SIZE = 10;
const int FRAME_SIZE = 4096; // 4KiB
const int UNIT_SIZE = 1048576; // 1MiB
const int FRAMES_TOTAL = UNIT_SIZE/FRAME_SIZE; // 256 frames


struct directoryEntry {
    char fileName[MAX_NAME_SIZE + 1];
    int firstFrameAddress = -1;
    char date[MAX_DATE_SIZE + 1];
    bool opened =  false;
    int frameCursor = -1; // cursor pointing to a frame in the unit
    int charCursor = 0; // cursor pointing to a char in the frame
    std::int8_t processId = -1; // Range: -128 to 127. We only use positive number to "process id"
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
    bool resetCursors(int directoryPosition);

public:
    FAT(/* args */);
    ~FAT();
    // Methods
    bool open(char *fileName, int processId);
    bool close(char *filename, int processId);
    bool create(char* filename, char* date);
    bool read(char* filename, char* buffer, int processID, int nChar);
    // The buffer must be at least one character longer than the line.
    bool getLine(char* filename, char* buffer, int bufferSize, int processID); // this will fail if the buffer length is less than the line length
    bool write(char* filename, int processID, char* data);
    int search(char* filename);
    bool append(char* filename, int processID, char* data);
    bool rename(char* filename, char* newFilename);
    void list(); // list files in directory
    void print(bool verbose = false);
    bool deleteFile(char* filename, int processID);
    int findEmptyFrame();
    bool searchCredentials(char *username, char *hash);
    bool loadFile(char* filename, int processID);
    bool saveFile(char* filename, int processID, char* writingName);
};

#endif