all:client server

client:client.o wrap.o common.o
	gcc -g -o $@ $^ -lpthread
server:server.o wrap.o common.o
	gcc -g -o $@ $^ -lpthread

%.o:%.c
	gcc -g -o $@ -c $^

.PHONY:clean
clean:
	rm -rf client server *.o

