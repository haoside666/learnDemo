all:client server
client:myclient.c
	gcc -g -o $@ $^ -lpthread
server:myserver.c
	gcc -g -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f client server
