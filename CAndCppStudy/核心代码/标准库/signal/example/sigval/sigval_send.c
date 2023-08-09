
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("arguments error!");
        exit(0);
    }

    pid_t pid=atoi(argv[1]);//�����̺�ת��Ϊ����
    union sigval v;
    v.sival_int=100;
    //���ֻ������SIGINT���������ݣ�
    //�κ��źŶ��У�ֻ��Ҫ���Ͷ�����ն˹涨һ�¼���
    sigqueue(pid,SIGINT,v);
    return 0;
}