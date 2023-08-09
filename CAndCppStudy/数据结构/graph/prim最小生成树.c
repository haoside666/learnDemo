#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图的邻接矩阵
#define MaxVertexNum 100
#define INFINITY 65536
#define ERROR -1
typedef int vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode *ptrToENode;
struct ENode
{
    vertex v1, v2;
    WeightType weight;
};
typedef ptrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode
{
    int vertexnumber; //顶点数
    int edgenumber; //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int vertexnum);
void insertEdge(MGraph mygraph, Edge E);
MGraph BuildGraph();
void freeGraph(MGraph mygraph);

int main(int argc, char *argv[])
{
    MGraph mygraph = BuildGraph();
    printf("\t");
    for (int i = 0; i < mygraph->vertexnumber; i++)
        printf("%c\t", mygraph->data[i]);
    printf("\n");
    for (int i = 0; i < mygraph->vertexnumber; i++)
    {
        printf("%c\t", mygraph->data[i]);
        for (int j = 0; j < mygraph->vertexnumber; j++)
        {
            printf("%d\t", mygraph->G[i][j]);
        }
        printf("\n");
    }
    freeGraph(mygraph);
    return 0;
}

MGraph CreateGraph(int vertexnum)
{
    MGraph mygraph = malloc(sizeof(struct GNode));
    mygraph->vertexnumber = vertexnum;
    mygraph->edgenumber = 0;
    memset(mygraph->G, 0, sizeof(WeightType) * MaxVertexNum * MaxVertexNum);
    return mygraph;
}

void insertEdge(MGraph mygraph, Edge E)
{
    mygraph->G[E->v1-1][E->v2-1] = E->weight;
    mygraph->G[E->v2-1][E->v1-1] = E->weight;
}

MGraph BuildGraph()
{

    int i;
    char choose;
    MGraph mygraph;
    Edge e;
    vertex vertexnum;
    printf("please input vertex number:");
    scanf("%d", &vertexnum);
    mygraph = CreateGraph(vertexnum);
    printf("please input edge number:");
    scanf("%d", &mygraph->edgenumber);
    if (mygraph->edgenumber != 0)
    {
        e = malloc(sizeof(struct ENode));
        for (i = 0; i < mygraph->edgenumber; i++)
        {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            insertEdge(mygraph, e);
        }
    }
    free(e);
    for (i = 0; i < mygraph->vertexnumber; i++)
    {
        while ((choose = getchar()) != '\n' && choose != EOF);
        scanf("%c", &mygraph->data[i]);
    }
    return mygraph;
}

void freeGraph(MGraph mygraph)
{
    if (mygraph != NULL)
        free(mygraph);
    mygraph = NULL;
}
/* 邻接矩阵存储 - Prim最小生成树算法 */
 
vertex FindMinDist(MGraph mygraph, WeightType dist[] )
{ /* 返回未被收录顶点中dist最小者 */
    vertex MinV, V;
    WeightType MinDist = INFINITY;
 
    for (V=0; V<mygraph->vertexnumber; V++) {
        if ( dist[V]!=0 && dist[V]<MinDist) {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回-1作为标记 */
}
 
int Prim( MGraph mygraph, MGraph MST)
{ 
    /* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
    WeightType dist[MaxVertexNum], TotalWeight;
    vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;
     
    /* 初始化。默认初始点下标是0 */
    for (V=0; V<mygraph->vertexnumber; V++) {
        /* 这里假设若V到W没有直接的边，则mygraph->G[V][W]定义为INFINITY */
           dist[V] = mygraph->G[0][V];
           parent[V] = 0; /* 暂且定义所有顶点的父结点都是初始点0 */ 
    }
    TotalWeight = 0; /* 初始化权重和     */
    VCount = 0;      /* 初始化收录的顶点数 */
    /* 创建包含所有顶点但没有边的图。注意用邻接表版本 */
    MST = CreateGraph(mygraph->vertexnumber);
    E = (Edge)malloc( sizeof(struct ENode) ); /* 建立空的边结点 */
            
    /* 将初始点0收录进MST */
    dist[0] = 0;
    VCount ++;
    parent[0] = -1; /* 当前树根是0 */
 
    while (1) {
        V = FindMinDist( mygraph, dist );
        /* V = 未被收录顶点中dist最小者 */
        if ( V==ERROR ) /* 若这样的V不存在 */
            break;   /* 算法结束 */
             
        /* 将V及相应的边<parent[V], V>收录进MST */
        E->v1 = parent[V];
        E->v2 = V;
        E->weight = dist[V];
        InsertEdge( MST, E );
        TotalWeight += dist[V];
        dist[V] = 0;
        VCount++;
         
        for( W=0; W<mygraph->vertexnumber; W++ ) /* 对图中的每个顶点W */
            if ( dist[W]!=0 && mygraph->G[V][W]<INFINITY ) {
            /* 若W是V的邻接点并且未被收录 */
                if ( mygraph->G[V][W] < dist[W] ) {
                /* 若收录V使得dist[W]变小 */
                    dist[W] = mygraph->G[V][W]; /* 更新dist[W] */
                    parent[W] = V; /* 更新树 */
                }
            }
    } /* while结束*/
    if ( VCount < mygraph->vertexnumber ) /* MST中收的顶点不到|V|个 */
       TotalWeight = ERROR;
    return TotalWeight;   /* 算法执行完毕，返回最小权重和或错误标记 */
}