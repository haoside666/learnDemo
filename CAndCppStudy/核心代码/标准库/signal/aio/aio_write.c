#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>

#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
    //定义aio控制块结构体
    struct aiocb wr;

    int ret,fd;

    char str[20] = {"hello,world"};

    bzero(&wr,sizeof(wr));
    fd = open("test.txt",O_WRONLY | O_APPEND);
    if(fd < 0)
    {
        perror("test.txt");
    }
    wr.aio_buf = str;

    //填充aiocb结构
    wr.aio_fildes = fd;
    wr.aio_nbytes = sizeof(str);

    //异步写操作
    ret = aio_write(&wr);
    if(ret < 0)
    {
        perror("aio_write");
    }

    //等待异步写完成
    while(aio_error(&wr) == EINPROGRESS)
    {
        printf("hello,world\n");
		usleep(1);
    }

    //获得异步写的返回值
    ret = aio_return(&wr);
    printf("\n\n\n返回值为:%d\n",ret);

    return 0;
}
