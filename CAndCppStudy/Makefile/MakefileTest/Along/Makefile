TARGET=exe
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
INCLUDE =
DEFS = 
CFLAGS = -g 
CC =gcc
LIBS =
RELEASE=release
SYMBOL=debug

$(TARGET):$(OBJ)
	$(CC) -g -o $@ $^ $(LIBS)
%.o:%.cpp
	$(CC) $(CFLAGS) $(DEFS) -o $@ -c $^ 
	
$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
	strip $(TARGET).release 
	
$(SYMBOL):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol
	
.PHONY:
clean:
	rm -rf *.o $(TARGET) $(TARGET).release $(TARGET).symbol .gdb_history


#$(TARGET):$(OBJ)
#	$(CC) $(CFLAGS) $(DEFS) -o $@ $^ $(LIBS)
