.PHONY : all client server compile-client compile-server compile run

all: compile run

run: server client

compile: compile-server compile-client

compile-client:
	gcc -o ./client/client ./client/main.c

compile-server:
	gcc -o ./server/server ./server/main.c

client:
	./client/client &

server:
	./server/server &
