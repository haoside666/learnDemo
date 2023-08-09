CC = gcc
TARGET = pthread_pool
SRC = pthread_pool.c base.c
OBJECT = pthread_pool.o  base.o
INCLUDES = -I./
LDFLAGS = -lpthread

all:$(TARGET)

#$(OBJECT):$(SRC)
#	$(CC) -c $(INCLUDES) ${SRC}

$(TARGET):$(OBJECT)
	$(CC) -g -o $@ $(OBJECT) $(LDFLAGS)

pthread_pool.o:pthread_pool.c
	$(CC) -c $(INCLUDES) $^ -g -o $@
base.o:base.c
	$(CC) -c $(INCLUDES) $^ -g -o $@
.PHONY:clean

clean:
	@rm -rf $(OBJECT) $(TARGET) *~

