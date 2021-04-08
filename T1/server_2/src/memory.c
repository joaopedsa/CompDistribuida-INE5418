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
    for(; i < tam_buffer && memorySize > (position + i); i++) {
        memory[(position + i)] = buffer[i];
    }
    
    // Rest Buffer
    char* restBuffer = malloc(sizeof(char*));
    int j = 0;
    while(i < tam_buffer) {
        restBuffer = realloc(restBuffer, sizeof(char));
        restBuffer[j] = buffer[i];
        i++;
        j++;
    }

    pthread_mutex_unlock(&mutex);
    return restBuffer;
}

char* readMemory(int position, int tam) {
    pthread_mutex_lock(&mutex);
    char* readBuffer = malloc(sizeof(char*));
    for(int i = 0; i < tam && memorySize > (position + i); i++) {
        readBuffer[i] = memory[(position + i)];
    }
    pthread_mutex_unlock(&mutex);

    return readBuffer;
}

char* readAllMemory() {
    return memory;
}
