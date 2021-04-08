#include <stdio.h>
#include <stdlib.h>

#include "./instruction.h"
#include "./memory.c"
#include "./utils.c"

char* executeInstruction(char* instruction, char** params) {
    if(strcmp(instruction, "write") == 0) {
        int position = atoi(params[0]);
        char* buffer = params[1];
        int tam_buffer = atoi(params[2]);
        buffer = writeMemory(position, buffer, tam_buffer);
        return buffer;
    } else if (strcmp(instruction, "read") == 0) {
        int position = atoi(params[0]);
        int tam = atoi(params[1]);
        return readMemory(position, tam);   
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