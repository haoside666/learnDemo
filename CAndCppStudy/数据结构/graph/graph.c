#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图的邻接矩阵
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *ptrToENode;
struct ENode
{
    Vertex v1, v2;
    WeightType weight;
};
typedef ptrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode
{
    int vertexnumber; //顶点数
    int edgenumber; //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int verternum);
void insertEdge(MGraph mygraph, Edge E);
MGraph BuildGraph();
void freeGraph(MGraph mygraph);
void FindAnimal(MGraph mygraph);
int main(int argc, char *argv[])
{
    MGraph mygraph = BuildGraph();
    FindAnimal(mygraph);
    freeGraph(mygraph);
    return 0;
}

MGraph CreateGraph(int vertexnum)
{
    MGraph mygraph = malloc(sizeof(struct GNode));
    mygraph->vertexnumber = vertexnum;
    mygraph->edgenumber = 0;
    for(int i=0;i<vertexnum;i++)
        for(int j=0;j<vertexnum;j++)
            mygraph->G[i][j]=INFINITY;
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
    MGraph mygraph;
    Edge e;
    Vertex verternum;
    scanf("%d", &verternum);
    mygraph = CreateGraph(verternum);
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
    return mygraph;
}

void freeGraph(MGraph mygraph)
{
    if (mygraph != NULL)
        free(mygraph);
    mygraph = NULL;
}

void Floyd( MGraph mygraph, WeightType D[][MaxVertexNum])
{
    Vertex i, j, k;
    /* 初始化 */
    for ( i=0; i<mygraph->vertexnumber; i++ )
        for( j=0; j<mygraph->vertexnumber; j++ ) {
            D[i][j] = mygraph->G[i][j];         
        }
 
    for( k=0; k<mygraph->vertexnumber; k++ )
        for( i=0; i<mygraph->vertexnumber; i++ )
            for( j=0; j<mygraph->vertexnumber; j++ )
                if( D[i][k] + D[k][j] < D[i][j] ) {
                    D[i][j] = D[i][k] + D[k][j];
                    if ( i==j && D[i][j]<0 ) /* 若发现负值圈 */
                        return;
                }
    return; /* 算法执行完毕，返回正确标记 */
}
WeightType FindMaxDist(WeightType D[][MaxVertexNum],Vertex i, int N )
{
    WeightType MaxDist;
    Vertex j;
    MaxDist = 0;
    for( j=0; j<N; j++ ) /* 找出i到其他动物j的最长距离 */
        if ( i!=j && D[i][j]>MaxDist )
        MaxDist = D[i][j];
    return MaxDist;
}

void FindAnimal( MGraph mygraph)
{  
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Vertex Animal, i;
    Floyd(mygraph, D);
    MinDist = INFINITY;
    for ( i=0; i<mygraph->vertexnumber; i++) 
    {
        MaxDist = FindMaxDist( D, i, mygraph->vertexnumber);
        if ( MaxDist == INFINITY ) { /* 说明有从i无法变出的动物 */
            printf("0\n");
            return;
        }
        if ( MinDist > MaxDist ) { /* 找到最长距离更小的动物 */
            MinDist = MaxDist;  Animal = i+1; /* 更新距离，记录编号 */
        }
    }
    printf("%d %d\n", Animal, MinDist);
}