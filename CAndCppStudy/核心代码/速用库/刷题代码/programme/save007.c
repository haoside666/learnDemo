#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 101
typedef enum{false,true} bool;
typedef int vertex;
typedef struct position
{
    int x;
    int y;
}pos_t;
struct MNode
{
    vertex vertexnumber;   //顶点数
    pos_t pos[MAXSIZE];
    int G[MAXSIZE][MAXSIZE];
};
typedef struct MNode* Graph;

bool visited[MAXSIZE];
Graph creatGraph(int N,int maxdistance);
bool DFS(Graph mygraph,vertex v,int distance);

int main(int argc,char *argv[])
{
    int N,maxdistance;
    Graph mygraph;
    scanf("%d %d",&N,&maxdistance);
    mygraph=creatGraph(N,maxdistance);
    if(DFS(mygraph,0,50-maxdistance))
    {
        printf("Yes\n");
    }else
    {
        printf("No\n");
    }    
	free(mtgraph);
    return 0;
}

Graph creatGraph(int N,int maxdistance)
{
    Graph mygraph=(Graph)malloc(sizeof(struct MNode)*(N+1));
    pos_t temp;
    temp.x=temp.y=0;
    mygraph->vertexnumber=N+1;
    mygraph->pos[0]=temp;
    for(int i=0;i<=N;i++)
    {
        visited[i]=false;
        for(int j=0;j<=N;j++)
        {
            mygraph->G[i][j]=0;
        }
    }
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d",&temp.x,&temp.y);
        for(int j=0;j<i;j++)
        {
            if(j==0)
            {
                if(pow(temp.x,2)+pow(temp.y,2)<=pow(maxdistance+7.5,2))
                {
                    mygraph->G[j][i]=1;
                    mygraph->G[i][j]=1;
                }
            }else
            {
                if(pow(temp.x-mygraph->pos[j].x,2)+pow(temp.y-mygraph->pos[j].y,2)<=pow(maxdistance,2))
                {
                    mygraph->G[j][i]=1;
                    mygraph->G[i][j]=1;
                }
            }           
        }
        mygraph->pos[i]=temp;
    }
    return mygraph;
}
bool DFS(Graph mygraph,vertex v,int distance)
{
    static bool flags=false;
    visited[v]=true;
    if(flags) return true;
    for(int i=0;i<mygraph->vertexnumber;i++)
    {     
		if(flags) return true;   
        if(!visited[i]&&mygraph->G[v][i]!=0)
        {
            if(mygraph->pos[i].x<=-distance||mygraph->pos[i].x>=distance||mygraph->pos[i].y<=-distance||mygraph->pos[i].y>=distance)
            {
                flags=true;
                return true;
            }
            DFS(mygraph,i,distance);
        }
    }
    return flags==true;
}
