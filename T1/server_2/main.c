#include <pthread.h>
#include <stdlib.h>

#include "main.h"
#include "./src/connection.c"

int main() {
    openServer(SIZE_MEMORY, SERVER_PORT);
    exit(0);
}