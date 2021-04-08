#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "./connection.h"
#include "./instruction.c"
#include "./utils.h"

void *threadClient(void *args) {
    char socketMessage[1024];
    struct ThreadArgs *threadargs = args; 
    int client_socket = threadargs->client_socket;
    while(1) {
        read(client_socket, socketMessage, sizeof(socketMessage));
        if(isSair(socketMessage)) {
            write(client_socket, socketMessage, sizeof(socketMessage));
            close(client_socket);
            pthread_exit(NULL);
            break;
        }

        char* instruction = findInstruction(socketMessage);
        char** params = findParams(socketMessage);;

        char* response = executeInstruction(instruction, params);

        write(client_socket, response, sizeof(socketMessage));
        memset(&socketMessage, 0, sizeof(socketMessage));
    }
}


void openServer(int sizeMemory, int port) {
    // Initialize Memory Server
    initMemory(sizeMemory);

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = port;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 25);
    printf("Server Listen on PORT: %d\n", server_address.sin_port);
    while(1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        struct ThreadArgs *threadArgs = malloc(sizeof(*threadArgs));
        threadArgs->client_socket = client_sockfd;
        pthread_t pthread;
        pthread_create(&pthread, NULL, threadClient, (void *)threadArgs);
    }
    close(server_sockfd);
}