CC = gcc
CXX = g++ 
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src)) 
target = $(patsubst %.c, %, $(src)) 
LIBS = -lpthread
CFLAGS += -g

all:$(target)
$(target):%:%.c
	$(CC) $^ $(CFLAGS) -o $@ $(LIBS)
#%.o:%.cpp
#	$(CC) $(CFLAGS) -c $< -o $@
.PHONY:
clean:
	-rm -rf $(target) *.o
