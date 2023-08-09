.PHONY:all
all:sendmsg recvmsg

sendmsg:sendmsg.c
	gcc -g -o $@ $^
recvmsg:recvmsg.c
	gcc -g -o $@ $^

.PHONY:clean
clean:
	rm -rf sendmsg recvmsg
