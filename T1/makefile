.PHONY : client server compile-client compile-servers compile run

compile: compile-server compile-client

compile-client:
	gcc -o ./client/client ./client/main.c

compile-servers:
	gcc -o ./server/server ./server/main.c -pthread && gcc -o ./server_1/server ./server_1/main.c -pthread && gcc -o ./server_2/server ./server_2/main.c -pthread

client:
	./client/client

servers:
	./server_2/server & ./server_1/server & ./server/server
