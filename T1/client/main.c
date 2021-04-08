#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void inputMessage(char* message) {
    char c;
    int i = 0;

    printf("Insert Message:\n");
    while((c = getchar()) != '\n') {
        message[i++] = c;
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
    char socketMessage[1024];
    char* writeMessage = "write(0,123,3)";
    char* readMessage = "read(0, 3)";
    char* logMessage = "log()";

    if(socketMessage == NULL) {
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
        sleep(1);
        write(sockfd, writeMessage, sizeof(socketMessage));
        read(sockfd, socketMessage, sizeof(socketMessage));
        printf("Escrita Feita: %s\n", socketMessage);
        memset(&socketMessage, 0, sizeof(socketMessage));
    }
}