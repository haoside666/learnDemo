#include "common.h"
void process1() //bash
{
    int len,fd;
    int msg_id = creat_queue(1);
    char buf[MAXBUF],temp_buf[MAXBUF];
    while (1)
    {
        sleep(1);
        memset(buf, '\0', sizeof(buf));
        int ret = recv_msg(msg_id, BASH_TYPE, buf, sizeof(buf));
        if(ret==0)
        {
            if(access(TEMPFILE_PATH,F_OK)==-1)
            {
                fd=open(TEMPFILE_PATH,O_TRUNC|O_WRONLY);
            }else
            {
                fd=open(TEMPFILE_PATH,O_CREAT|O_TRUNC|O_WRONLY,0666);
            }
            
            dup2(fd,1);
            dup2(fd,2);
            system(buf);
            close(fd);
            fd=open(TEMPFILE_PATH,O_RDONLY);
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
    delete_queue(msg_id);
}
int main()
{
    process1();
    return 0;
}