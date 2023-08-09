.PHONY:all
all:shm_sem_example_recv  shm_sem_example_send

shm_sem_example_recv:shm_sem_example_recv.c
	gcc -g -o $@ $^
shm_sem_example_send:shm_sem_example_send.c
	gcc -g -o $@ $^

.PHONY:clean
clean:
	rm -rf shm_sem_example_recv shm_sem_example_send
