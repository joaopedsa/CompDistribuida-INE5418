#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

// Local Imports
#include "./connection.c"
#include "./memory.c"

int main() {
    char* buffer = initMemory(250);
    int* server_sockfd = malloc(sizeof(int));
    openConnection(server_sockfd);
    waitConnection(server_sockfd);
    close(*server_sockfd);
    exit(0);
}