TARGET=student.exe
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

INCLUDE =-I.
DEFS=
CFLAGS=-g -o
CC=gcc
LIBSPATH=
LIBS=
RELEASE=release
SYMBOL=debug

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $@ $^ $(LIBSPATH) $(LIBS)
%.o:%.c
	$(CC) -g -o $@ -c $(INCLUDE) $^ 

$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
	strip $(TARGET).release

$(SYMBOL):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol

.PHONY:
clean:
	del -rf *.o $(TARGET) $(TARGET).release $(TARGET).symbol
