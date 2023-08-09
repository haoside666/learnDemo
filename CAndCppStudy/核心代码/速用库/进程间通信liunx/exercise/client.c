#include"common.h"

int client()
{
    int msg_id = get_queue(1);
    char buf[MAXBUF],temp_buf[MAXBUF];
    printf("##");
	while(fgets(buf, MAXBUF, stdin) != NULL)
	{
		int ret=send_msg(msg_id, BASH_TYPE, buf);
		if(ret==-1)
		{
		    perror("msgsnd error");
		    return -1;
		}
		while(1)
		{
		    ret=recv_msg(msg_id, BASH_REPLY_TYPE,temp_buf,MAXBUF);
		    if(ret==0)
		    {
		        if(strcmp(temp_buf,"error")==0)
		        {
		            perror("send_msg fail");
		            exit(EXIT_FAILURE);
		        }else if(strcmp(temp_buf,"end")==0)
		        {
		            break;
		        }else
		        {
		           	fprintf(stdout,"%s",temp_buf);
					fflush(stdout);
		        } 
		    }      
		}
        printf("##");
	}
}
int main(int argc ,char *argv[])
{
    client();
    return 0;
}
