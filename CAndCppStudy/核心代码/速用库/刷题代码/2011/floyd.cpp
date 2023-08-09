#include<cstdio>
#include <limits.h>
#include <iostream>
#include <iomanip>
using namespace std;

const int maxn=4;
int dist[maxn][maxn];//记录距离矩阵
int path[maxn][maxn];//path[i][j]=x表示i到j的路径上(除i外)的第一个点是x.
void init()
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
        {
            dist[i][j] = i==j?0:INT_MAX;//其实这里d[i][j]应该还要通过输入读数据的
            // dist[i][j] = INT_MAX;//其实这里d[i][j]应该还要通过输入读数据的
            path[i][j]=-1;
        }
 
    //读取其他dist[i][j]的值
    dist[0][2]=2;
    dist[1][0]=3;
    dist[2][1]=4;
    dist[2][3]=2;
    dist[3][0]=5;
    dist[3][1]=1;
}

void print(int A[maxn][maxn],int type)
{
    for(int i=0;i<maxn;i++)
    {
        for(int j=0;j<maxn;j++){
            if(type==0)
            {
                if(A[i][j]==INT_MAX)
                {
                    cout<<setw(10)<<"INF";
                }else{
                    cout<<setw(10)<<A[i][j];
                }
            }else{
                switch(A[i][j])
                {
                    case 0:
                        cout<<setw(10)<<'A';
                        break;
                    case 1:
                        cout<<setw(10)<<'B';
                        break;
                    case 2:
                        cout<<setw(10)<<'C';
                        break;
                    case 3:
                        cout<<setw(10)<<'D';
                        break;
                    default:
                        cout<<setw(10)<<path[i][j];
                        break;
                }
            }
        }
        cout<<endl;
    }
}
 
void floyd()
{
    for(int k=0;k<maxn;k++)
    {
        for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
        if(dist[i][k]<INT_MAX && dist[k][j]<INT_MAX)
        {
            if(dist[i][j]>dist[i][k]+dist[k][j])
            {
                dist[i][j] = dist[i][k]+dist[k][j];
                path[i][j] = k;
            }
        }
        print(dist,0);
        cout<<"--------------------------------------"<<endl;
        cout<<"第"<<k<<"行:"<<endl;
        print(path,1);
        cout<<"--------------------------------------"<<endl<<endl<<endl;
    }
}


int main()
{
    //读n和m
    init();
    print(dist,0);
    cout<<"--------------------------------------"<<endl;
    print(path,1);
    cout<<"--------------------------------------"<<endl<<endl<<endl;
    //读m条边
    floyd();
    //输出所求最短路径距离

    return 0;
}
