CC = gcc
#CFLAGS = -O2 -Wall -I .
CFLAGS = -g -I . 

#If you support https,then LIB=-DHTTPS -lpthread -lssl -lcrypto
#else LIB=-lpthread
LIB = -lpthread -lssl -lcrypto 
#LIB = -lpthread 
 

UFLAGS= -std=c99 -W -Wall
UFLAGS+= -O3
UFLAGS+= -g -fno-omit-frame-pointer -fsanitize=address
UFLAGS+= -Iinclude
LDFLAGS+= -L$(PWD)/lib -luaparser.0.2.0 -lpcre
all: uaparser webd

uaparser: util/uaparser.c
	$(CC) $(UFLAGS) util/uaparser.c $(LDFLAGS) -o uaparser
	
webd: main.c wrap.o parse_config.o daemon_init.o parse_option.o log.o secure_access.o cgi
	$(CC) $(CFLAGS) -o $@  main.c wrap.o parse_config.o daemon_init.o parse_option.o log.o secure_access.o $(LIB) 

wrap.o: wrap.c
	$(CC) $(CFLAGS) -c wrap.c

parse_config.o: parse_config.c parse.h
	$(CC) $(CFLAGS) -c parse_config.c

daemon_init.o: daemon_init.c parse.h
	$(CC) $(CFLAGS) -c daemon_init.c

parse_option.o: parse_option.c parse.h
	$(CC) $(CFLAGS) -c parse_option.c $(LIB)

log.o: log.c parse.h
	$(CC) $(CFLAGS) -c log.c

secure_access.o: secure_access.c  parse.h
	$(CC) $(CFLAGS) -c secure_access.c

cgi:
	(cd cgi-bin; make)

clean:
	rm -f *.o webd  uaparser access.log *~
	(cd cgi-bin; make clean)

