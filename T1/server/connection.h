struct ThreadArgs {
    int client_socket;
};
void *CreateClient(void *args);

void waitConnection(int *server_sockfd);

void openConnection(int *server_sockfd, struct sockaddr_in *server_address, int port);
