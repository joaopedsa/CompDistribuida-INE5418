#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Local Imports
#include <./connection.h>
#include <./memory.h>

int main() {
    int server_sockfd;
    struct sockaddr_in server_address;
    char* buffer = initMemory(250);
    openConnection(&server_sockfd, &server_address);
    waitConnection(&server_sockfd);
    close(server_sockfd);
    exit(0);
}