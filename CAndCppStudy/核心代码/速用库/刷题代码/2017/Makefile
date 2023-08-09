CC = gcc
CXX = g++ 
src = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(src)) 
target = $(patsubst %.cpp, %, $(src)) 
LIBS =
CFLAGS += -g

all:$(target)
$(target):%:%.cpp
	$(CXX) $^ $(CFLAGS) -o $@
#%.o:%.cpp
#	$(CXX) $(CFLAGS) -c $< -o $@
.PHONY:
clean:
	-rm -rf $(target) *.o
