#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAXSIZE 30

typedef struct node
{
    int data;
    struct node *left,*right;
    struct node *next;
}Link,*TreeLink;

//快速排序
void QuickSort(vector<int> &v,int low,int high)
{
    if(low<high){
        int i=low,j=high;
        int pivot = v[low];    //将第一个元素作为枢轴
        //接下来进行第一次partition
        while(i<j){
            while(i<j && v[j]>=pivot)    //从右往左找到第一个小于枢轴的数
                j--;
            if(i<j){    //将该数移动到左指针的位置
                v[i] = v[j];
                i++;
            }
            while(i<j && v[i]<pivot)    //从左往右找到第一个大于等于枢轴的数
                i++;
            if(i<j){    //将该数移动到右指针的位置
                v[j] = v[i];
                j--;
            }
        }
        v[i] = pivot;    //循环退出时i == j即枢轴的位置
        //递归处理当前枢轴的左右两部分
        QuickSort(v,low,i-1);    
        QuickSort(v,i+1,high);
    }
}

TreeLink Create(vector<int>& v)
{
    QuickSort(v,0,v.size()-1);
    TreeLink head=new Link;
    head->left=head->right=head->next=NULL;
    TreeLink p,tail=head;
    for(int i=0;i<v.size();i++)
    {
        p=new Link;
        p->data=v[i];
        p->next=p->left=p->right=NULL;
        tail->next=p;
        tail=p;
    }
    return head;
}

TreeLink HuffmanTree(TreeLink head)
{
    TreeLink p=NULL,q=NULL,s;
    while(head->next->next)
    {
        p=head->next;
        q=p->next;
        if(q->next!=NULL)
        {
            head->next=q->next;
        }else{
            head->next=NULL;

        }
        s=new Link;
        s->data=p->data+q->data;
        s->left=p;
        s->right=q;
        p=head;
        while(p->next!=NULL)
        {
            if(s->data>p->next->data)
            {
                p=p->next;
            }else{
                s->next=p->next;
                p->next=s;
                break;
            }
        }
        if(p->next==NULL)
        {
            s->next=p->next;
            p->next=s;   
        }
    }
    return head;
}


void LevelorderTraversal(TreeLink t)
{
    int i=1,j=1,m,size;
	if(t==NULL) return;
	queue<TreeLink> myqueue;
	myqueue.push(t);
	TreeLink temp;
    vector<int> v;
    m=1;
	while(!myqueue.empty())
	{
        m--;
		temp=myqueue.front();
        myqueue.pop();
		printf("%d ",temp->data);
        
		if(temp->left)
		{
            myqueue.push(temp->left);
		}
		if(temp->right)
		{
            myqueue.push(temp->right);
		}
        if(m==0)
        {
            cout<<endl;
            m=myqueue.size();
        }
	}
	printf("\n");
}


int main()
{
    vector<int> v={24,16,6,20,10,30};
    TreeLink t=Create(v);
    TreeLink s=HuffmanTree(t);
    LevelorderTraversal(s->next);
    return 0;
}