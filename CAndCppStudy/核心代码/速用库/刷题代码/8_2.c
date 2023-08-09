#include <stdio.h>
#include <string.h>
typedef struct {
    int t,p,flag;
} Queue;
Queue Q[1010];
void ChkVip(int start,int end,int sum) {
    int i,pos;
    for(i=start; i<end; i++) {
        if(Q[i].flag==1&&Q[i].t<sum) {//查看是否有VIP客户已经在等待
            pos=i;
            break;
        }
    }
    if(i<end) {//VIP客户插队
        Queue tmp=Q[pos];
        for(i=pos-1; i>=start; i--) {
            Q[i+1]=Q[i];
        }
        Q[start]=tmp;
    }
}
int main() {
    int n,i,min;
    scanf("%d",&n);
    int front=0,rear=0;
    for(i=0; i<n; i++) {
        scanf("%d %d %d",&Q[rear].t,&Q[rear].p,&Q[rear].flag);
        if(Q[rear].p>60)Q[rear].p=60;
        rear++;
    }
    int k,c;
    scanf("%d %d",&k,&c);
    int sum[k],winnum[k];
    memset(sum,0,sizeof(sum));
    memset(winnum,0,sizeof(winnum));
    int SWT=0,WT=0,LWT=0;
    while(front<rear) {
        if(Q[front].flag==0) {//队头是普通客户
            min=0;
            for(i=0; i<k; i++) {//查找空闲窗口
                if(Q[front].t>=sum[i]) {//此时无需等待
                    if(i==c)//当前空闲窗口是VIP窗口，则查找此时是否有Vip客户已经到时来，若vip已经到来，则将vip插队上来
                        ChkVip(front,n,sum[i]);
                    sum[i]=Q[front].t+Q[front].p;
                    front++;
                    winnum[i]++;
                    break;
                }
                if(sum[i]<sum[min])
                    min=i;
            }
            if(i==k) {//已经到来在等待
                if(min==c)//当前空闲窗口是VIP窗口，则查找此时是否有Vip客户已经到时来，若vip已经到来，则将vip插队上来
                    ChkVip(front,n,sum[min]);
                WT=sum[min]-Q[front].t;
                if(WT>LWT)LWT=WT;
                SWT+=WT;
                sum[min]+=Q[front].p;
                front++;
                winnum[min]++;

            }
        } else {//队头是VIP客户
            if(Q[front].t>=sum[c]) {//查找此时是否有VIP窗口空闲
                sum[c]=Q[front].t+Q[front].p;
                winnum[c]++;
                front++;
            } else {
                min=c;
                for(i=0; i<k; i++) {//查找最快完成窗口
                    if(sum[i]<sum[min])
                        min=i;
                }
                if(Q[front].t>=sum[min])//无需等待
                    sum[min]=Q[front].t+Q[front].p;
                else {//需等待
                    WT=sum[min]-Q[front].t;
                    if(WT>LWT)LWT=WT;
                    SWT+=WT;
                    sum[min]+=Q[front].p;
                }
                front++;
                winnum[min]++;
            }
        }
    }
    int LFT=0;
    for(i=0; i<k; i++) {
        if(sum[i]>sum[LFT])
            LFT=i;
    }
    printf("%.1lf %d %d\n",(double)SWT/n,LWT,sum[LFT]);
    for(i=0; i<k; i++) {
        if(i>0)
            printf(" ");
        printf("%d",winnum[i]);
    }
    return 0;
}