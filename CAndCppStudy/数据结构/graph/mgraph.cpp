#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

//图的邻接矩阵
typedef int Vertex;
typedef int WeightType;
typedef string DataType;

struct ENode
{
	Vertex v1, v2;
	WeightType weight;
};

struct info
{
	Vertex V;
	int index;
};
class MGraph
{
public:
	MGraph() = default;

	void insertEdge(const ENode& E)
	{
		G[E.v1 - 1][E.v2 - 1] = E.weight;
		G[E.v2 - 1][E.v1 - 1] = E.weight;
	}
	void BuildGraph()
	{
		int i;
		ENode e;
		cout << "please input vertex number:";
		cin >> vertexnumber;
		cout << "please input edge number:";
		cin >> edgenumber;
		G.assign(vertexnumber, vector<WeightType>(vertexnumber));
		data.assign(vertexnumber, "");
		visited.assign(vertexnumber, false);
		if (edgenumber != 0)
		{
			for (i = 0; i < edgenumber; i++)
			{
				cin >> e.v1 >> e.v2 >> e.weight;
				insertEdge(e);
			}
		}
		for (i = 0; i < vertexnumber; i++)
		{
			cout << "please ebter the " << i + 1 << " vertex:";
			cin >> data[i];
		}
	}
	void print()
	{
		cout << "\t";
		for (int i = 0; i < vertexnumber; i++)
			cout << data[i] << "\t";
		cout << endl;
		for (int i = 0; i < vertexnumber; i++)
		{
			cout << data[i] << "\t";
			for (int j = 0; j < vertexnumber; j++)
			{
				cout << G[i][j] << "\t";
			}
			cout << endl;
		}
	}

	void BFS()
	{

	}
	void DFS(Vertex V)
	{
		visited[V - 1] = true;
		cout << "正在访问" << data[V - 1] << "顶点" << endl;
		for (int i = 0; i<vertexnumber; i++)
		{
			if (!visited[i] && G[V - 1][i] != 0)
			{
				DFS(i + 1);
			}
		}
	}

	void DFS2(Vertex V)
	{
		visited.assign(vertexnumber, false);
		int i;
		info temp;
		info posinfo;
		posinfo.V = V;
		posinfo.index = 0;
		mystack.push(posinfo);
		visited[V - 1] = true;
		cout << "正在访问" << data[V - 1] << "顶点" << endl;
		while (!mystack.empty())
		{
			temp = mystack.top();
			for (i = temp.index; i < vertexnumber; i++)
			{
				if (!visited[i] && G[temp.V - 1][i] != 0)
				{
					mystack.top().index = i+1;
					posinfo.V = i+1;
					posinfo.index = 0;
					mystack.push(posinfo);
					visited[i] = true;
					cout << "正在访问" << data[i] << "顶点" << endl;
					break;
				}
			}
			if (i == vertexnumber)
				mystack.pop();
		}
	}
private:
	int vertexnumber; //顶点数
	int edgenumber; //边数
	vector<vector<WeightType> > G;
	vector<DataType> data;
	vector<bool> visited;
	stack<info> mystack;
};

int main(int argc, char *argv[])
{
	int i=0,sum=0;
	for(int i=0;i<100;i++)
	{
		sum+=i;
	}
	MGraph mygraph;
	mygraph.BuildGraph();
	mygraph.print();
	mygraph.DFS(1);
	cout << "----------------------------------" << endl;
	mygraph.DFS2(1);
	return 0;
}

