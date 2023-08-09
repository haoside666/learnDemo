.SUFFIXES:.c .o
CC = gcc
SRCS = server.c\
    pub.c\
    thread_work.c
OBJS = $(SRCS:.c=.o)

CFLAGS= -std=c99 -W -Wall
CFLAGS+= -O3
CFLAGS+= -g -fno-omit-frame-pointer -fsanitize=address
CFLAGS+= -Iinclude
LDFLAGS+= -L$(PWD)/lib -luaparser.0.2.0 -lpcre
all: uaparser server

uaparser: util/uaparser.c
	$(CC) $(CFLAGS) util/uaparser.c $(LDFLAGS) -o uaparser
server:$(OBJS)
	$(CC) -o $@ $^ -lpthread
%.o:%.c
	$(CC) -g -o $@ -c $<
clean:
	rm -f $(OBJS) server uaparser

