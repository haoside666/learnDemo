.PHONY:all
all:send recv

recv:recv.c common.c
	gcc -g -o $@ $^
send:send.c common.c
	gcc -g -o $@ $^

.PHONY:clean
clean:
	rm -rf recv send
