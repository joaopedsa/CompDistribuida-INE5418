#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// Local Imports
#include "connection.h"

void *CreateClient(void *args) {
    char* socketMessage;
    struct ThreadArgs *threadargs = args;
    int client_socket = threadargs->client_socket;
    while(1) {
        read(client_socket, socketMessage, sizeof(socketMessage));
        printf("Message Receive from Client: %s\n", socketMessage);
    }
}

void waitConnection(int *server_sockfd) {
    while(1) {
        struct sockaddr_in client_address;
        int client_sockfd;
        int client_len = sizeof(client_address);
        client_sockfd = accept(*server_sockfd, (struct sockaddr *)&client_address, &client_len);
        struct ThreadArgs *threadArgs = malloc(sizeof(*threadArgs));
        threadArgs->client_socket = client_sockfd;
        pthread_t pthread;
        pthread_create(&pthread, NULL, CreateClient, (void *)threadArgs);
    }
}

void openConnection(int* server_sockfd) {
    struct sockaddr_in server_address;
    *server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 3456;
    int server_len = sizeof(server_address);
    bind(*server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(*server_sockfd, 25);
    printf("Open Connection on Port: %d\n", server_address.sin_port);
}