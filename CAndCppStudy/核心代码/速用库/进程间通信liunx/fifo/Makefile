.PHONY:all
all:client server

client:client.c
	gcc -g -o client client.c
server:server.c
	gcc -g -o server server.c
.PHONY:clean
clean:
	rm -f client server
