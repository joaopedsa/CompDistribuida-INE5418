char* writeInMemories(int position, char* buffer, int tam_buffer);
char* readMemories(int position, int tam);
char* executeInstruction(char* instruction, char** params);
char* sendMessageToNode(int port, char* message);
int isSair(char* input);
char* findInstruction(char* socketMessage);
char** findParams(char* socketMessage);