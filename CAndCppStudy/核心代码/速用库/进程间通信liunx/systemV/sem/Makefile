all:productor customer

productor:sem_productor.c
	gcc -g -o $@ $^
customer:sem_customer.c
	gcc -g -o $@ $^

.PHONY:clean
clean:
	rm -rf productor customer
