#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

// Local Imports
#include "./connection.c"
#include "./memory.c"

int main() {
    char* buffer = initMemory(250);
    int server_sockfd;
    struct sockaddr_in server_address;
    openConnection(server_sockfd, server_address, 3000);
    waitConnection(server_sockfd);
    close(server_sockfd);
    exit(0);
}