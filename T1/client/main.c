#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char chooseOperation() {
    char c;
    printf("Escolha a operação a executar no servidor:\n");
    printf("1 - Ler\n");
    printf("2 - Escrever\n");
    c = getchar();
    return c;
}

int main() {
    int sockfd;
    int len;
    struct sockaddr_in address;
    char* buffer = "TESTE";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 3456;
    len = sizeof(address);
    int result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("ops");
        exit(1);
    }
    while(1) {
        char c = chooseOperation();
        write(sockfd, buffer, sizeof(buffer));
        close(sockfd);
    }
}