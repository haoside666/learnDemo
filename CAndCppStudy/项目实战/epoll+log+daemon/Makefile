TARGET=daemon_epoll_lcx

$(TARGET):printlog.c epoll_lcx.c
	gcc -g -o $@ $^ -lrt -lpthread

.PHONY:
clean:
	-rm -rf $(TARGET) 
