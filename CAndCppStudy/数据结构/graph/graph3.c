#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;
typedef enum{false,true}bool;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex v; //邻接点下标
    WeightType weight;
    PtrToAdjVNode next;
};

typedef struct VNode
{
    PtrToAdjVNode firstedge;
    DataType data; //存顶点的数据
} AdjList[MaxVertexNum];

typedef struct LNode *PtrToLNode;
struct LNode
{
    int Vertexnumber; //顶点数
    int edgenumber;   //边数
    AdjList G;        //邻接表
};
typedef PtrToLNode LGraph;

typedef struct ENode *ptrToENode;
struct ENode
{
    Vertex v1, v2;
    WeightType weight;
};
typedef ptrToENode Edge;

bool Visited[MaxVertexNum]={false};

LGraph CreateLGraph(int Vertexnum);
void insertEdge(LGraph mygraph, Edge E);
LGraph BuildGraph();
void freeGraph(LGraph mygraph);
void freeNode(PtrToAdjVNode head);
void printList(PtrToAdjVNode head);
void Visit(LGraph mygraph,Vertex V);
void DFS(LGraph mygraph, Vertex V, void (*Visit)(LGraph mygraph,Vertex V));

int main(int argc, char **argv)
{
    LGraph mygraph=BuildGraph();
    for(int i=0;i<mygraph->Vertexnumber;i++)
    {
        printf("%c\t",mygraph->G[i].data);
        printList(mygraph->G[i].firstedge);
    }
	printf("DFS:\n");
	DFS(mygraph,1,Visit);
	freeGraph(mygraph);
    return 0;
}
//创建一个没有边的图
LGraph CreateLGraph(int Vertexnum)
{
    LGraph mygraph = malloc(sizeof(struct LNode));
    mygraph->Vertexnumber = Vertexnum;
    mygraph->edgenumber = 0;
    for (int i = 0; i < Vertexnum; i++)
    {
        mygraph->G[i].firstedge = NULL;
    }
	return mygraph;
}

void insertEdge(LGraph mygraph, Edge E)
{
    PtrToAdjVNode temp=malloc(sizeof(struct AdjVNode));
    temp->v=E->v2;
    temp->weight=E->weight;
    temp->next=mygraph->G[E->v1-1].firstedge;
    mygraph->G[E->v1-1].firstedge=temp;

    //无向图则两次
     PtrToAdjVNode temp2=malloc(sizeof(struct AdjVNode));
    temp2->v=E->v1;
    temp2->weight=E->weight;
    temp2->next=mygraph->G[E->v2-1].firstedge;
    mygraph->G[E->v2-1].firstedge=temp2;
}

LGraph BuildGraph()
{
    int i;
    char choose;
    int Vertexnum;
    Edge e;
    LGraph mygraph;
	printf("please input vertex number:");
    scanf("%d",&Vertexnum);
    mygraph=CreateLGraph(Vertexnum);
	printf("please input edge number:");
    scanf("%d",&mygraph->edgenumber);
    if(mygraph->edgenumber!=0)
    {
        e=malloc(sizeof(struct ENode));
        for(i=0;i<mygraph->edgenumber;i++)
        {
            scanf("%d %d %d",&e->v1,&e->v2,&e->weight);
            insertEdge(mygraph,e);
        }
        free(e);
        for(i=0;i<Vertexnum;i++)
        {
            while((choose=getchar()!='\n'&&choose!=EOF));
            scanf("%c",&mygraph->G[i].data);
        }
    }
    return mygraph;
}

void freeGraph(LGraph mygraph)
{
    int i;
    for(int i=0;i<mygraph->Vertexnumber;i++)
    {
        freeNode(mygraph->G[i].firstedge);
    }
    free(mygraph);
}

void freeNode(PtrToAdjVNode head)
{
    PtrToAdjVNode p=head;
    PtrToAdjVNode q=head;
    while(p!=NULL)
    {
        q=q->next;
        free(p);
        p=q;
    }
}

void printList(PtrToAdjVNode head)
{
    PtrToAdjVNode p=head;
    while(p!=NULL)
    {
        printf("%d %d\t",p->v,p->weight);
        p=p->next;
    }
    printf("\n");
}

void Visit(LGraph mygraph,Vertex V)
{
    printf("正在访问顶点%c\n", mygraph->G[V-1].data);
}
 
/* Visited[]为全局变量，已经初始化为false */
void DFS(LGraph mygraph, Vertex V, void (*Visit)(LGraph mygraph,Vertex V))
{   /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
    PtrToAdjVNode p;
     
    Visit(mygraph,V); /* 访问第V个顶点 */
    Visited[V] = true; /* 标记V已访问 */
 
    for( p=mygraph->G[V-1].firstedge; p; p=p->next ) /* 对V的每个邻接点W->AdjV */
        if (!Visited[p->v])    /* 若W->AdjV未被访问 */
            DFS(mygraph,p->v,Visit);    /* 则递归访问之 */
}
