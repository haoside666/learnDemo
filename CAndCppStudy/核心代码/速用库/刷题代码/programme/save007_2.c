#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 101
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

struct firstjump
{
	double distance;
	int index;
};
int dist[MAXSIZE];
int path[MAXSIZE];
int end,num=0;
struct firstjump onejump[MAXSIZE];
Graph creatGraph(int N, int maxdistance);
int BFS(Graph mygraph, vertex v, int distance);
int main(int argc, char *argv[])
{
	int k = 0;
	int mystack[MAXSIZE];
	int N, maxdistance, number, temp;
	Graph mygraph;
	scanf("%d %d", &N, &maxdistance);
	mygraph = creatGraph(N, maxdistance);
	if (maxdistance + 7.5 >= 50) { printf("1\n"); return 0; }
	number = BFS(mygraph, 0, 50 - maxdistance);
	printf("%d\n", number);
	if (number != 0)
	{
		while (end != 0)
		{
			mystack[k++] = end;
			end = path[end];
		}
		for (int i = k - 1; i >= 0; i--)
		{
			temp = mystack[i];
			printf("%d %d\n", mygraph->pos[temp].x, mygraph->pos[temp].y);
		}
	}
	free(mygraph);
	return 0;
}

Graph creatGraph(int N, int maxdistance)
{
	Graph mygraph = (Graph)malloc(sizeof(struct MNode)*(N + 1));
	pos_t temp;
	double distance;
	int cnt = 1;
	temp.x = temp.y = 0;
	mygraph->pos[0] = temp;
	for (int i = 0; i <= N; i++)
	{
		dist[i] = 0;
		for (int j = 0; j <= N; j++)
		{
			mygraph->G[i][j] = 0;
		}
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &temp.x, &temp.y);
		if (temp.x <= -50 || temp.x >= 50 || temp.y <= -50, temp.y >= 50 || pow(temp.x, 2) + pow(temp.y, 2) <= pow(7.5, 2))
			continue;

		for (int j = 0; j<cnt; j++)
		{
			if (j == 0)
			{
				distance = pow(temp.x, 2) + pow(temp.y, 2);
				if (distance <= pow(maxdistance + 7.5, 2))
				{
					onejump[num].distance = distance;
					onejump[num].index = cnt;
					num++;
					mygraph->G[j][cnt] = 1;
					mygraph->G[cnt][j] = 1;
				}
			}
			else
			{
				if (pow(temp.x - mygraph->pos[j].x, 2) + pow(temp.y - mygraph->pos[j].y, 2) <= pow(maxdistance, 2))
				{
					mygraph->G[j][cnt] = 1;
					mygraph->G[cnt][j] = 1;
				}
			}
		}
		mygraph->pos[cnt++] = temp;
	}
	mygraph->vertexnumber = cnt;
	return mygraph;
}

int compare(const void *a,const void* b)
{
	struct firstjump* aa = (struct firstjump*)a;
	struct firstjump* bb = (struct firstjump*)b;
	return (int)(aa->distance-bb->distance);
}
int BFS(Graph mygraph, vertex v, int distance)
{
	int myqueue[MAXSIZE];
	dist[v] = 1;
	path[v] = -1;
	int i, front = 0, rear = 0, temp;
	qsort(onejump,num,sizeof(struct firstjump),compare);
	for (int i = 0; i < num;i++)
		myqueue[rear++] = onejump[i].index;
	while (front != rear)
	{
		temp = myqueue[front++];
		for (i = 0; i<mygraph->vertexnumber; i++)
		{
			if (!dist[i] && mygraph->G[temp][i] != 0)
			{
				if (mygraph->pos[i].x <= -distance || mygraph->pos[i].x >= distance || mygraph->pos[i].y <= -distance || mygraph->pos[i].y >= distance)
				{					
					path[i] = temp;
					end = i;
					return dist[temp] + 1;
				}
				path[i] = temp;
				dist[i] = dist[temp] + 1;
				myqueue[rear++] = i;
			}
		}			
	}
	return 0;
}

