#include <stdio.h>

// Position Server
char* getServerLog(int position) {
    char* message = "log()";
    char* result = sendMessageToNode(SERVERS_PORTS[position], message);
    return result;
}

char* getAllLogs() {
    int numberServers = (int)(sizeof(SERVERS_PORTS) / sizeof(int));
    char* memory = readAllMemory();
    char* memories = malloc(sizeof(char*));
    strcat(memories, memory);
    for(int i = 0; i < numberServers; i++) {
        memory = getServerLog(i);
        strcat(memories, memory);
    }
    return memories;
}

void writeLog() {
    FILE *f = fopen("log.txt", "w");
    char* result = getAllLogs();
    fputs(result, f);
    free(result);
    fclose(f);
}

void *initializeLogger() {
    while(1) {
        sleep(5);
        writeLog();
    }
}