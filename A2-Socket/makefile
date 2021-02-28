.PHONY : client server compile-client compile-server compile run

compile: compile-server compile-client

compile-client:
	gcc -o ./client/client ./client/main.c

compile-server:
	gcc -o ./server/server ./server/main.c

client:
	./client/client

server:
	./server/server
