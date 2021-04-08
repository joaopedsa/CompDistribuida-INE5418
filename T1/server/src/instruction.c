#include <stdio.h>
#include <stdlib.h>

#include "./instruction.h"
#include "./memory.c"
#include "./utils.c"

char* writeInMemories(int position, char* buffer, int tam_buffer) {
    char* restBuffer = writeMemory(position, buffer, tam_buffer);
    tam_buffer = strlen(restBuffer);
    int serverPosition = 0;
    while(tam_buffer != 0) {
        char* message = messageWrite(0, restBuffer, tam_buffer);
        char* response = sendMessageToNode(SERVERS_PORTS[serverPosition], message);
        tam_buffer = strlen(response);
        restBuffer = response;
        serverPosition++;
    }
    return buffer;
}

char* readInMemories(int position, int tam) {
    char* buffer = readMemory(position, tam);
    int restTam = tam - strlen(buffer);
    int serverPosition = 0;
    while(restTam > 0) {
        char* message = messageRead(0, restTam);
        char* response = sendMessageToNode(SERVERS_PORTS[serverPosition], message);
        restTam = restTam - strlen(response);
        strcat(buffer, response);
        serverPosition++;
    }
    return buffer;
}

char* sendMessageToNode(int port, char* message) {
    char socketMessage[1024];
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    int len;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = port;
    len = sizeof(server_address);
    int result = connect(sockfd, (struct sockaddr *)&server_address, len);
    write(sockfd, message, sizeof(socketMessage));
    read(sockfd, socketMessage, sizeof(socketMessage));
    close(sockfd);
    char* response = socketMessage;
    return response;
}

char* executeInstruction(char* instruction, char** params) {
    if(strcmp(instruction, "write") == 0) {
        int position = atoi(params[0]);
        char* buffer = params[1];
        int tam_buffer = atoi(params[2]);
        buffer = writeInMemories(position, buffer, tam_buffer);
        return buffer;
    } else if (strcmp(instruction, "read") == 0) {
        int position = atoi(params[0]);
        int tam = atoi(params[1]);
        return readInMemories(position, tam);   
    } else {
        return readAllMemory();
    }
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
    while(socketMessage[i] != '(' && socketMessage[i] != '\0') {
        action = realloc(action, sizeof(char));
        action[i] = socketMessage[i];
        i++;
    }
    return action;
}

char** findParams(char* socketMessage) {
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