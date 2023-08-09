#include "parse.h"

int init_daemon()
{
	int i;
	pid_t pid;
	struct sigaction sa;
	umask(0);
	if(pid=fork())
		exit(0);
	else if(pid<0)
		exit(1);
	setsid();

	sa.sa_handler=SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sigaction(SIGHUP,&sa,NULL);


	if(pid=fork())
		exit(0);
	else if(pid<0)
		exit(1);

	chdir("/");
    close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
    return 1;
}
