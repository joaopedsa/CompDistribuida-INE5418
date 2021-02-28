#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct Operation {
    char operador;
    char** operandos;
};

struct ThreadArgs {
    int client_socket;
};

char** getOperandos(char* socketMessage) {
    char** operandos = NULL;
    int lenOperando = 0;
    int numberOperando = 0;
    operandos = malloc(sizeof(char*));
    int i = 0;
    while(socketMessage[i] != '\0') {
        if(socketMessage[i] != '+' & socketMessage[i] != '-' & socketMessage[i] != '*' & socketMessage[i] != '/') {
            operandos[numberOperando] = realloc(operandos[numberOperando], sizeof(char));
            operandos[numberOperando][lenOperando] = socketMessage[i];
            lenOperando++;
        } else {
            operandos = realloc(operandos, sizeof(char*));
            numberOperando++;
            lenOperando = 0;
        }
        i++;
    }
    return operandos;
}

char getOperador(char* socketMessage) {
    char operador;
    int i = 0;
    while(socketMessage[i] != '\0') {
        if(socketMessage[i] == '+' | socketMessage[i] == '-' | socketMessage[i] == '*' | socketMessage[i] == '/') {
            operador = socketMessage[i];
            break;
        }
        ++i;
    }
    return operador;
}

int doOperation(char operation, int number1, int number2) {
    switch (operation) {
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        case '/':
            return number1 / number2;
        default:
            return 0;
    }
}

int calculate(struct Operation operation) {
    int i = 0;
    int j = 0;
    char operador = operation.operador;
    int number1 = atoi(operation.operandos[0]);
    int number2 = atoi(operation.operandos[1]);
    return doOperation(operador, number1, number2);
}

char* getResult(char* socketMessage) {
    struct Operation operation;
    operation.operador = getOperador(socketMessage);
    operation.operandos = getOperandos(socketMessage);

    int resultInteger = calculate(operation);

    char* result = malloc(20 * sizeof(char));

    sprintf(result, "%d", resultInteger);

    return result;
}

int isSair(char* input) {
    char* verifyInput = "sair";
    if (strcmp(verifyInput, input) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void *threadClient(void *args) {
    struct ThreadArgs *threadargs = args; 
    int client_socket = threadargs->client_socket;
    char socketMessage[250];
    while(1) {
        read(client_socket, socketMessage, sizeof(socketMessage));
        if(isSair(socketMessage)) {
            write(client_socket, socketMessage, sizeof(socketMessage));
            close(client_socket);
            pthread_exit(NULL);
            break;
        }
        printf("Operação Recebida do Cliente: %s\n", socketMessage);
        char* result = getResult(socketMessage);
        printf("Resultado da Operação: %s\n", result);
        write(client_socket, result, sizeof(result));
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