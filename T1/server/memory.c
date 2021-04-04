#include "memory.h"

char* buffer;

char* initMemory(int tam_buffer) {
    buffer = malloc(sizeof(char) * tam_buffer);
    return buffer;
}

char readMemory(int position, int size) {
    return buffer[position];
}

void writeMemory(int position, int size) {
    char* readBuffer;
    return buffer[position];
}
