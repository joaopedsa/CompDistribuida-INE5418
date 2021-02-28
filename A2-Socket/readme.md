# **Como Rodar:**

## Compilação:
Na pasta raiz utilizar o comando para compilar o servidor e cliente com as flags necessárias:

	make compile

Caso queira compilar sem utilizar o make basta executar os seguintes comandos:

	gcc -o ./server/server ./server/main.c -pthread  & gcc -o ./client/client ./client/main.c

## Execução do Server:

Na pasta raiz utilizar:

	make server

Caso queira executar sem utilizar o make basta executar o seguinte comando:

	./server/server

## Execução do Client:

Na pasta raiz utilizar:

	make client

Caso queira executar sem utilizar o make basta executar o seguinte comando:

	./client/client
