struct ThreadArgs {
    int client_socket;
};

int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;


void *threadClient(void *args);

void openServer(int sizeMemory, int port);