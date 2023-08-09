/*
accept signal
*/
#include "signal_handler.h"
static void sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( pipefd[1], &msg, 1, 0 );
    errno = save_errno;
}

static void addsig( int sig )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}




static void* handle_signal_event(void* handle_event_msg)
{
    handle_event_msg_t*event_msg=(handle_event_msg_t*)handle_event_msg;
	event_handler_t *self = event_msg->eh;
	//uint32_t e = handle_event_msg->e;
	int sig,ret;
	ret = recv(self->fd,&sig,sizeof(sig),0);
	if (ret <= 0)
	{
		printf("handle_signal_event recv err\n");
	}
	else
	{
		switch(sig)
		{
			case SIGALRM:
				alarm(TIMESLOT);
				printf("signal alarm\n");
                free(event_msg);
			break;
			case SIGINT:
				printf("signal int\n");
                free(event_msg);
				exit(0);
			break;
            
		}
	}
    free(event_msg);
    return NULL;
}


event_handler_t* create_signal_accepter(reactor_t* r,int sig)
{
	event_handler_t* eh = malloc(sizeof(event_handler_t));
	int ret = socketpair( PF_UNIX, SOCK_STREAM, 0, pipefd );
    assert( ret != -1 );
	eh->fd = pipefd[0];
	eh->reactor = r;
	eh->handle_event = &handle_signal_event;
	
	addsig( sig );
	return eh;
}