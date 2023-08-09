#include"common.h"

int server()
{
	int len,fd;
    int msg_id = creat_queue(1);
    char buf[MAXBUF],temp_buf[MAXBUF],_buf[MAXBUF];
    while(1)
    {
        sleep(1);
        memset(buf, '\0', MAXBUF);
        int ret = recv_msg(msg_id, BASH_TYPE, buf, sizeof(buf));
        if(ret==0)
        {
            memset(temp_buf, '\0', MAXBUF);
            if(strncasecmp(buf, "cd", 2)==0)
            {
                if(buf[2]!=' ')
                {
                    sprintf(temp_buf,"command not found %s\n",buf);
                    send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
                }
                memcpy(_buf,&buf[3],MAXBUF-3);
                ret=chdir(_buf);
                if(ret==-1)
                {
                    sprintf(temp_buf,"%s\n",strerror(errno));
                    send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
                }
                strcpy(temp_buf,"end");
                send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
                continue;
            }
            if(access(TEMPFILE_PATH,F_OK)==0)
            {
                fd=open(TEMPFILE_PATH,O_TRUNC|O_WRONLY);
            }else
            {
                fd=open(TEMPFILE_PATH,O_CREAT|O_TRUNC|O_WRONLY,0666);
            }
            if(fd<0)
			{
				perror("open error");
				return -1;
			}
            dup2(fd,1);
            dup2(fd,2);
            system(buf);
            close(fd);
            fd=open(TEMPFILE_PATH,O_RDONLY);
			if(fd<0)
			{
				perror("open error");
				return -1;
			}
            while((len=read(fd, temp_buf,MAXBUF)))
            {
                if(len==-1)
                {
                    strcpy(temp_buf,"error");
                    send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
                }else
                {
                    send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
                }
            }
            strcpy(temp_buf,"end");
            send_msg(msg_id,BASH_REPLY_TYPE,temp_buf);
            close(fd);
		}
    }
    return delete_queue(msg_id);
}
int main()
{
    server();
    return 0;
}
