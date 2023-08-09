#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void sys_err(char *str)
{
	perror(str);
	exit(1);
}
int main(void)
{
	pid_t pid;
	int i;
	for (i = 0; i < 5; i++) {
		if ((pid = fork()) == 0)
			break;
		else if (pid < 0)
			sys_err("fork");
	}
	if (pid == 0) {
		int n = 5;
		while (n--) {
			printf("child ID %d--%d\n", getpid(),i);
			sleep(1);
		}
		return i;
	}
	else if (pid > 0) {
		printf("------%d-------\n",wait(NULL));
		printf("------%d-------\n",wait(NULL));
		printf("------%d-------\n",wait(NULL));
		printf("------%d-------\n",wait(NULL));
		printf("------%d-------\n",wait(NULL));
		pause();
	}
	return 0;
}
