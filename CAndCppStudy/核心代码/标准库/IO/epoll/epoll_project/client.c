#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./wrap.h"
#include "./common.h"

int main(int argc,char *argv[])
{
	int len;
    package_t pkg;
    char buf[MAXBUF+1024];
	if (argc != 3) {
		printf("usage: ./client destip destport\n");
		exit(1);
	}
	//create socket
	int sockfd=Socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	inet_pton(AF_INET,SERVERIP, &seraddr.sin_addr.s_addr);
	seraddr.sin_port = htons(SERVERPORT);
  
	//connect
	Connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    packageTostr(buf, &pkg);
    len=Write(sockfd, buf, strlen(buf));
    if (len < 0) {
        printf ("package send failure\n");
    }            
    strcpy(pkg.dest_ip,argv[1]);
    pkg.dest_port=atoi(argv[2]);
    while(1);
	
	return 0;
}

