#include <pthread.h>

#include "./memory.h"


void initMemory(int size) {
    memorySize = size;
    memory = (char*) calloc(size, sizeof(char));
}

char* writeMemory(int position, char* buffer, int tam_buffer) {
    pthread_mutex_lock(&mutex);
    int i = 0;
    
    // Write on Memory
    for(; i < tam_buffer && i < memorySize; i++) {
        memory[(position + i)] = buffer[i];
    }
    
    // Rest Buffer
    char* restBuffer = malloc(sizeof(char*));
    for(; i < memorySize; i++) {
        restBuffer = realloc(restBuffer, sizeof(char));
        restBuffer[(position + i)] = buffer[i];
    }

    pthread_mutex_unlock(&mutex);
    return restBuffer;
}

char* readMemory(int position, int tam) {
    pthread_mutex_lock(&mutex);
    char* readBuffer = malloc(sizeof(char*));
    for(int i = 0; i < tam; i++) {
        readBuffer = realloc(readBuffer, sizeof(char));
        readBuffer[i] = memory[(position + i)];
    }
    pthread_mutex_unlock(&mutex);

    return readBuffer;
}

char* readAllMemory() {
    return memory;
}
