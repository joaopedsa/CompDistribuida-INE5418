#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char* buffer;

void initMemory(int tam_buffer) {
    buffer[tam_buffer];
    return &buffer;
}

void readMemory(int position, int size) {
    char* readBuffer;
    return buffer[position];
}