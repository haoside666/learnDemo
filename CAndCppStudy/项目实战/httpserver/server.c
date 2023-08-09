#include "thread_work.h"
#include "pub.h"
int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("usage:server port \n");
		return 0;
	}
	int port = atoi(argv[1]);

	if(port <= 0)
	{
		printf("port must be positive integer: \n");
		return 0;
	}

	int st =socket_create(port);
	if(st==0)
	{
		return 0;
	}
	setdaemon();
    memset(LOGBUF,0,sizeof(LOGBUF));
	sprintf(LOGBUF,"[+] my http server begin\n");
	save_log(LOGBUF);
	socket_accept(st);
	close(st);
}
