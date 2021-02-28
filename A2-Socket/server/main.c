#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

struct Operation {
    char operador;
    char** operandos;
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

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char socketMessage[250];
    char* result;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 3456;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);
    printf("Server Listen on PORT: %d\n", server_address.sin_port);
    while(1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        read(client_sockfd, socketMessage, sizeof(socketMessage));
        printf("Operação Recebida do Cliente: %s\n", socketMessage);
        result = getResult(socketMessage);
        printf("Resultado da Operação: %s\n", result);
        write(client_sockfd, result, sizeof(result));
        close(client_sockfd);
    }
    close(server_sockfd);
    exit(0);
}