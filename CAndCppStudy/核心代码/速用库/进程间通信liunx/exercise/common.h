#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdint.h>
#include <fcntl.h>
#define _PATH1_ "/"
#define _PATH2_ "/home"
#define _PATH3_ "/tmp"
#define _PROJ_ID_ 0x6666
#define _SIZE_ 8192
#define OPEN_MAX 1024
#define MAXBUF 4096

#define MSG_QUEUE_TYPE 1
#define GENERAL_TYPE 2

#define TEMPFILE_PATH "./temp.txt"
#define BASH_TYPE 1
#define FILE_UPLOAD_TYPE 2
#define FILE_DOWNLOAD_TYPE 3
#define BASH_REPLY_TYPE 4
#define FILE_UPLOAD_REPLY_TYPE 5
#define FILE_DOWNLOAD_REPLY_TYPE 6

struct msgbuf
{
    long mtype;
    char mtext[MAXBUF];
};

static int com_creat_queue(int flags,int mode);
extern int creat_queue();
extern int get_queue();
extern int send_msg(int msgqueue_id,int who,char *msg);
extern int recv_msg(int msgqueue_id,int want,char out[],int out_len);
extern int delete_queue(int msgqueue_id);

#endif
