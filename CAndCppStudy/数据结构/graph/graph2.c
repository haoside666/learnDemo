#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 1000
typedef int Vertex;
struct Edge
{
	Vertex v1, v2;
};

struct GNode
{
    int vertexnumber; 
    int edgenumber;
    int G[MaxVertexNum][MaxVertexNum];
};
typedef enum{false,true}bool;
typedef struct GNode* MGraph;
bool visited[MaxVertexNum];
MGraph BuildGraph();
void SDS(MGraph mygraph);
int BFS(MGraph mygraph,Vertex v);

int main(int argc,char *argv[])
{
    MGraph mygraph=BuildGraph();
    SDS(mygraph);
    free(mygraph);
    return 0;
}
MGraph BuildGraph()
{	
    MGraph mygraph=(MGraph)malloc(sizeof(struct GNode));
    struct Edge e;
    scanf("%d",&mygraph->vertexnumber);
    scanf("%d",&mygraph->edgenumber);
    for(int i=0;i<mygraph->vertexnumber;i++)
    {
        visited[i]=false;
        for(int j=0;j<mygraph->vertexnumber;j++)
        {
            mygraph->G[i][j]=0;
        }
    }
    
    for (int i = 0; i < mygraph->edgenumber;i++)
    {
        scanf("%d %d",&e.v1,&e.v2);
        mygraph->G[e.v1-1][e.v2-1] = 1;
        mygraph->G[e.v2-1][e.v1-1] = 1;
    }
	return mygraph;
}

void SDS(MGraph mygraph)
{
    int count;
    for (int i = 0; i < mygraph->vertexnumber;i++) {
        count = BFS(mygraph,i);
        printf("%d: %.2lf%%\n",i+1,count*100.0/mygraph->vertexnumber);
        for(int j=0;j<mygraph->vertexnumber;j++)
        {
            visited[j]=false;
        }
    }
}

int BFS(MGraph mygraph,Vertex v)
{
    int count = 1;
    int myqueue[MaxVertexNum+1];
    int front=0,rear=1;
    int level = 0,last=v;
    visited[v] = true;
    myqueue[0]=v;
    Vertex temp;
    while (front!=rear) {
        temp = myqueue[front];
        front++;
        for (int i = 0; i <mygraph->vertexnumber; i++)
        {
            if (!visited[i]&&mygraph->G[temp][i]!=0) {
                myqueue[rear++]=i;
                visited[i] = true;
                count++;
            }
        }
        if (temp == last)
        {
            level++;
			if(front!=rear)
            	last=myqueue[rear-1];   
			else
				 break;
        }
        if (level == 6) break;
    }
    return count;
}
