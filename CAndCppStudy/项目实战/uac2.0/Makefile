CC ?= clang
CFLAGS= -std=c99 -W -Wall
CFLAGS+= -O3
CFLAGS+= -g -fno-omit-frame-pointer -fsanitize=address

NAME= uaparser
MAJVER=  0
MINVER=  2
RELVER=  0
VERSION= $(MAJVER).$(MINVER).$(RELVER)

SLIB= lib$(NAME).a
DLIB= lib$(NAME).$(VERSION).so

CFLAGS+= -Iinclude -I.
LDFLAGS+= -L. -luaparser.0.2.0 -lpcre

.PHONY: all
all: uaparser

uaparser: util/uaparser.c
	$(CC) $(CFLAGS) util/uaparser.c $(LDFLAGS) -o uaparser

.PHONY: clean
clean:
	rm -rf uaparser
