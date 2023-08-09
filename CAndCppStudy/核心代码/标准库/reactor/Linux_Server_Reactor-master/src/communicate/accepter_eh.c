//accept and receive socket
#include "accepter_eh.h"
static void* package_handler(void* handle_event_msg)
{
    handle_event_msg_t*event_msg=(handle_event_msg_t*)handle_event_msg;
	printf("package_handler\n");
	int n;
	event_handler_t *self = event_msg->eh;
	uint32_t e = event_msg->e;
	common_package_t *package;
	package = malloc(sizeof(common_package_t));
	receive_msg_t *receive_msg = malloc(sizeof(receive_msg_t));
	if (e & EPOLLRDHUP)
	{
		printf("client down\n");
	}
	else if (e & EPOLLIN)
	{
//		n = recv(self->fd, package, MAXRECVLEN, 0);
//	    if( n <= 0 )
//	    {
//	        printf("recv err\n");
//	        close( self->fd );
//	    }
//	    printf("package_>body is %s\n",package->body );
//	    strcpy(package->body,"asdasdasdasdasd");
//	    n = send(self->fd,package,sizeof(common_package_t),0);
        data_handler();
	    // receive_msg->fd = self->fd;
	    // strcpy(receive_msg->ip,"127.0.0.1");
	    // reveive_message(receive_msg);

		free(package);
		free(receive_msg);
		free(event_msg);	
	}
	return NULL;
	
}

static event_handler_t* create_package_operater(int fd,reactor_t *r)
{
	printf("create_package_operater\n");
	event_handler_t* eh = malloc(sizeof(event_handler_t));
	eh->fd = fd;
	eh->reactor = r;
	eh->handle_event = &package_handler;
	return eh;
}

static void* handle_event(void* handle_event_msg)
{
    handle_event_msg_t*event_msg=(handle_event_msg_t*)handle_event_msg;
	event_handler_t *self = event_msg->eh;
	printf("acceptor_handle_event\n");
	int cli_fd = -1;
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);

	memset(&cli_addr, 0, sizeof(cli_addr));

	cli_fd = accept(self->fd, (struct sockaddr*) &cli_addr, &cli_addr_len);
	printf("accept fd is %d\n",cli_fd );
	event_handler_t* ceh = create_package_operater(cli_fd, self->reactor);
	self->reactor->add_eh(self->reactor, ceh);
	printf("handle_event ends\n");
	free(event_msg);
    return NULL;
}

event_handler_t* create_acceptor(int fd, reactor_t* r)
{
    // create event_handler
	event_handler_t* eh = malloc(sizeof(event_handler_t));
	eh->fd = fd;
	eh->reactor = r;
	eh->handle_event = &handle_event;

	return eh;
}