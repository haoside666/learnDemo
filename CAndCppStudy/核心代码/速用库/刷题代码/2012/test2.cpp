#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ElemType=int;
typedef struct Node
{
    ElemType elem;
    struct Node *next;
}Node,*linklist;

//冒泡排序 升序
void BobSort(vector<int> &v)
{
    int temp;
    bool flags;
    for(int i=0;i<v.size()-1;i++)
    {
        flags=true;
        for(int j=0;j<v.size()-1-i;j++)
        {
            if(v[j]>v[j+1])
            {
                temp=v[j];
                v[j]=v[j+1];
                v[j+1]=temp;
                flags=false;
            }
        }
        if(flags) return;
    }
}

ostream& operator<<(ostream &os,const vector<ElemType>&v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        os<<v[i]<<" ";
    }
    os<<endl;
    return os;
}

Node* createList(vector<ElemType>& v)
{
    BobSort(v);
    linklist head=new Node;
    head->next=NULL;
    Node *p;
    for(int i=0;i<v.size();i++)
    {
        if(i>0&&v[i]==v[i-1]) continue;
        p=new Node;
        p->elem=v[i];
        p->next=head->next;
        head->next=p;
    }
    return head;
}

void printList(linklist head)
{
	linklist p=head->next;
	while(p)
	{		
		printf("%d ",p->elem);
		p=p->next;		
	}
	printf("\n");
}
void deleteList(linklist head)
{
	linklist p,q;
	p=head->next;
	q=head->next;
	while(p)
	{	
		q=q->next;
		free(p);	
		p=q;	
	}	
	free(head);
}

int main()
{
    vector<ElemType> v={5,3,6,5,5,5,2,2,2,21,43,12};
    cout<<"原数组:"<<v;
    linklist head=createList(v);
    printList(head);
    deleteList(head);
    return 0;
}