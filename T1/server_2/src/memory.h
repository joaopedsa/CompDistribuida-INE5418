pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char* memory;
int memorySize;

void initMemory(int size);
char* writeMemory(int position, char* buffer, int tam_buffer);
char* readMemory(int position, int tam);
char* readAllMemory();

