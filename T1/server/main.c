#include <pthread.h>
#include <stdlib.h>

#include "main.h"
#include "./src/connection.c"
#include "./src/logger.c"

pthread_t pthreadLog;


int main() {
    pthread_create(&pthreadLog, NULL, initializeLogger, NULL);
    // Tamanho da Memória, Porta do Servidor
    openServer(SIZE_MEMORY, SERVER_PORT);
    exit(0);
}