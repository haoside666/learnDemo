CC = gcc
CFLAGS = -g -O2 -Wall -I ..

all: getAuth  postAuth webshell

getAuth: getAuth.c
	$(CC) $(CFLAGS) -o getAuth getAuth.c

postAuth: postAuth.c
	$(CC) $(CFLAGS) -o postAuth postAuth.c

webshell:webshell.c
	$(CC) $(CFLAGS) -o webshell webshell.c
clean:
	rm -f getAuth postAuth webshell *~
