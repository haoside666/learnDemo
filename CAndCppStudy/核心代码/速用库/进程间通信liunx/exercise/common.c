#include"common.h"
//function
static int com_creat_queue(int flags,int mode)
{
    char path[10];
    switch(mode)
    {
        case 1:
            strcpy(path,_PATH1_);
            break;
        case 2:
            strcpy(path,_PATH2_);
            break;
        case 3:
            strcpy(path,_PATH3_);
            break;
    }
    key_t key = ftok(path,_PROJ_ID_);
    if(key < 0){
        printf("%d:%s\n",errno,strerror(errno));
        return -1;
    }
    int msg_id = msgget(key,flags);
    if(msg_id < 0){
        printf("%d:%s\n",errno,strerror(errno));
        return -2;
    }
    return msg_id;
}

int creat_queue(int mode)
{
    int flags = IPC_CREAT|0666;
    return com_creat_queue(flags,mode);
}

int get_queue(int mode)
{
    int flags = IPC_CREAT;
    return com_creat_queue(flags,mode);
}

int send_msg(int msg_id,int who,char *msg)
{
    struct msgbuf _buf;
    memset(&_buf,'\0',sizeof(_buf));
    _buf.mtype = who;
    strncpy(_buf.mtext,msg,MAXBUF);
    return msgsnd(msg_id,&_buf,sizeof(_buf.mtext),0);
}
int recv_msg(int msg_id,int want,char out[],int out_len)
{
    struct msgbuf _buf;
    memset(&_buf,'\0',sizeof(_buf));
    int ret = msgrcv(msg_id,&_buf,sizeof(_buf.mtext),want,0);
	if(ret <= -1)
    {
        printf("%d:%s\n",errno,strerror(errno));
        return -1;
    }
    memset(out,'\0',out_len);
    strcpy(out,_buf.mtext);
    return 0;
}
int delete_queue(int msg_id)
{
    int ret = msgctl(msg_id,IPC_RMID,NULL);
    if(ret < 0){
        printf("%d:%s\n",errno,strerror(errno));
        return -3;
    }
    return 0;
}
