TARGET=getconfig
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

CC=gcc
INCLUDE=-I.
CFLAGS=-g
LIB = -DHTTPS -lpthread -lssl -lcrypto
DEFS=

RELEASE=release
SYMBOL=debug

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(DEFS) -o $@ $^ $(LIB) 

$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
	strip $(TARGET).release

$(SYMBOL):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol

.PHONY:
clean:
	-rm -rf *.o $(TARGET) $(TARGET).release $(TARGET).symbol

