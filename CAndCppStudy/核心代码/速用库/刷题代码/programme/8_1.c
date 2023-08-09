#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10 //最大开设的营业窗口数
#define MAXHANDTIME 60//最大处理时间
struct window
{
    int surplus_time; //窗口处理事务剩余时间
    int number;       //窗口处理事务个数
}windows[MAXSIZE];

struct customerinfo
{
    int arrival_time; //到达时间
    int handling_time;//事务处理时间
};
typedef struct customerinfo* CINFO;
void init()
{
    for(int i=0;i<MAXSIZE;i++)
    {
        windows[i].surplus_time=0;
        windows[i].number=0;
    }
}
int manage(int del_time,int handling_time,int K)
{
    int i;
    int min=60;
    int minindex=0;
    int latency_time;
    for(i=0;i<K;i++)
    {
        if(windows[i].surplus_time==0) continue;
        windows[i].surplus_time=windows[i].surplus_time-del_time>0?windows[i].surplus_time-del_time:0;
    }
    for(i=0;i<K;i++)//找到要排队的窗口
    {
        if(windows[i].surplus_time==0) break;
        if(windows[i].surplus_time<min)
        {
            min=windows[i].surplus_time;
            minindex=i;
        }
    }
    if(handling_time>MAXHANDTIME)handling_time=MAXHANDTIME;
    if(i==K)
    {
        latency_time=windows[minindex].surplus_time;
        windows[minindex].number++;
        windows[minindex].surplus_time+=handling_time;        
    }else
    {
        latency_time=windows[i].surplus_time;
        windows[i].number++;
        windows[i].surplus_time+=handling_time;
    }
    return latency_time;
}

int main(int argc,char *argv[])
{
    int N,K;
    int latency_time=0;
    int max_latency_time=0;
    int end_time;
    int temp=0;
    init();
    scanf("%d",&N);
    CINFO info=(CINFO)malloc(sizeof(struct customerinfo)*(N+1));
    info[0].arrival_time=info[0].handling_time=0;
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d",&info[i].arrival_time,&info[i].handling_time);        
    }
    scanf("%d",&K);

    for(int i=1;i<=N;i++)
    {        
        latency_time+=manage(info[i].arrival_time-info[i-1].arrival_time,info[i].handling_time,K);     
        if(latency_time>max_latency_time) max_latency_time=latency_time;
    }
    end_time=info[N].arrival_time;
    for(int i=0;i<K;i++)
    {
        if(windows[i].surplus_time>temp)temp=windows[i].surplus_time;
    }
    end_time+=temp;
    printf("%.1lf %d %d\n",1.0*latency_time/N,max_latency_time,end_time);
    printf("%d",windows[0].number);
    for(int i=1;i<K;i++)
    {
        printf(" %d",windows[i].number);
    }
    printf("\n");
    free(info);
    return 0;
}
