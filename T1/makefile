.PHONY : client server_main server_1 compile-client compile-servers compile run

compile: compile-server compile-client

compile-client:
	gcc -o ./client/client ./client/main.c

compile-servers:
	gcc -o ./server/server ./server/main.c -pthread && gcc -o ./server_1/server ./server_1/main.c -pthread

client:
	./client/client

server_1:
	./server_1/server

server_main:
	./server/server
