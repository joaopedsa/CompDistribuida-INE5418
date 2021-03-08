#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void inputOperations(char* operations) {
    char c;
    int i = 0;

    printf("Insira os dados para a calculadora:\n");
    while((c = getchar()) != '\n') {
        operations[i++] = c;
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

int main() {
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char operations[20];

    if(operations == NULL) {
        printf("Could not allocate memory!");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 3456;
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("ops: client1");
        exit(1);
    }
    printf("Connected Client on PORT: %d \n", address.sin_port);

    while(1) {
        inputOperations(operations);
        write(sockfd, operations, sizeof(operations));
        read(sockfd, operations, sizeof(operations));
        if(isSair(operations)) {
            exit(0);
        }
        printf("Resultado: %s\n", operations);
        memset(&operations, 0, sizeof(operations));
    }
}