TARGET=app
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

CC=gcc
INCLUDE=-I.
CFLAGS=-g
LDFLAGS=
DEFS=

RELEASE=release
SYMBOL=debug

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^ 

$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
	strip $(TARGET).release

$(SYMBOL):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol

.PHONY:
clean:
	-rm -rf *.o $(TARGET) $(TARGET).release $(TARGET).symbol .gdb_history

