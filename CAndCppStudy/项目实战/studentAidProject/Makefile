TARGET=exe
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
INCLUDE =
DEFS = 
CFLAGS = -g 
CC =g++
LIBS =
RELEASE=release
SYMBOL=debug

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LIBS)
%.o:%.cpp
	$(CC) $(CFLAGS) $(DEFS) -o $@ -c $^ 
	
$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
	strip $(TARGET).release 
	
$(SYMBOL):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol
	
.PHONY:
clean:
	rm -rf *.o $(TARGET) $(TARGET).release $(TARGET).symbol


#$(TARGET):$(OBJ)
#	$(CC) $(CFLAGS) $(DEFS) -o $@ $^ $(LIBS)
