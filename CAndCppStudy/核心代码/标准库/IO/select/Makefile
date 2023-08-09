all:client server

client:client.o wrap.o
	gcc -g -o $@ $^ -lpthread
server:server.o wrap.o
	gcc -g -o $@ $^ -lpthread

%.o:%.c
	$(CC) -g -o $@ -c $^

.PHONY:clean
clean:
	rm -rf client server *.o

