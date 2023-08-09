CC = gcc
CXX = g++ 
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src)) 
target = $(patsubst %.c, %, $(src)) 
LIBS =
CFLAGS += -g

all:$(target)
$(target):%:%.c
	$(CC) $^ $(CFLAGS) -o $@
#%.o:%.cpp
#	$(CXX) $(CFLAGS) -c $< -o $@
.PHONY:
clean:
	-rm -rf $(target) *.o
