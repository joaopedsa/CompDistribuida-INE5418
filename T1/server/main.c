#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char memory[250];

char* writeMemory(int position, char* buffer, int tam_buffer) {
    for(int i = 0; i < tam_buffer; i++) {
        memory[(position + i)] = buffer[i];
    }
    return buffer;
}

char* readMemory(int position, int tam) {
    char* readBuffer = malloc(sizeof(char*));
    for(int i = 0; i < tam; i++) {
        readBuffer = realloc(readBuffer, sizeof(char));
        readBuffer[i] = memory[(position + i)];
    }
    return readBuffer;
}

char* executeInstruction(char* instruction, char** params) {
    int cmp = strcmp(instruction, "escrever");
    if(cmp == 0) {
        int position = atoi(params[0]);
        char* buffer = params[1];
        int tam_buffer = atoi(params[2]);
        writeMemory(position, buffer, tam_buffer);
        return buffer;
    } else {
        int position = atoi(params[0]);
        int tam = atoi(params[1]);
        return readMemory(position, tam);
    }
    return "";
}

int isSair(char* input) {
    char* verifyInput = "sair";
    if (strcmp(verifyInput, input) == 0) {
        return 1;
    } else {
        return 0;
    }
}

char* findInstruction(char* socketMessage) {
    int i = 0;
    char* action = malloc(sizeof(char*));
    while(socketMessage[i] != '(') {
        action = realloc(action, sizeof(char));
        action[i] = socketMessage[i];
        i++;
    }
    return action;
}

char** findParams(char* socketMessage) {
    printf("Mensagem %s\n", socketMessage);
    char** params = NULL;
    int lenParams = 0;
    int numberParams = 0;
    params = malloc(sizeof(char*));
    int i = 0;

    while(socketMessage[i] != '(') {
        i++;
    }

    while(socketMessage[i] != '\0' & socketMessage[i] != ')') {
        
        if(socketMessage[i] == '"' | socketMessage[i] == ' ' | socketMessage[i] == '(') {
            i++;
            continue;
        }

        if(socketMessage[i] != ',') {
            params[numberParams] = realloc(params[numberParams], sizeof(char));
            params[numberParams][lenParams] = socketMessage[i];
            lenParams++;
        } else {
            params = realloc(params, sizeof(char*));
            numberParams++;
            lenParams = 0;
        }
        i++;
    }
    return params;
}

struct ThreadArgs {
    int client_socket;
};

void *threadClient(void *args) {
    struct ThreadArgs *threadargs = args; 
    int client_socket = threadargs->client_socket;
    char socketMessage[1024];
    while(1) {
        read(client_socket, socketMessage, sizeof(socketMessage));
        if(isSair(socketMessage)) {
            write(client_socket, socketMessage, sizeof(socketMessage));
            close(client_socket);
            pthread_exit(NULL);
            break;
        }
        // Posição 0 a instrução e Posição 1 os parametros
        char* instruction = findInstruction(socketMessage);
        char** params = findParams(socketMessage);
        printf("Instrução: %s\n", instruction);
        printf("Primeiro Parametro: %s\n", params[0]);

        pthread_mutex_lock(&mutex);
        char* response = executeInstruction(instruction, params);
        pthread_mutex_unlock(&mutex);

        printf("Response: %s\n", response);
        write(client_socket, response, sizeof(socketMessage));
        memset(&socketMessage, 0, sizeof(socketMessage));
    }
}

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 3456;
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
    exit(0);
}