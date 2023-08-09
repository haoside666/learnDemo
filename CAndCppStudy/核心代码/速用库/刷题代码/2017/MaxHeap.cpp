#include <limits.h>
#include <iostream>
#include <iomanip>
using namespace std;

typedef int ElementType;
typedef struct HeapNode* MaxHeap;
struct HeapNode
{
	ElementType* v;
	int tail;
	int capacity;
};

MaxHeap create(int maxsize);
void insert(MaxHeap h,ElementType data);
ElementType DeleteMax(MaxHeap h);
bool isfull(MaxHeap h);
bool isEmpty(MaxHeap h);
void freeheap(MaxHeap h);
ElementType* makemaxheap(ElementType arr[]);
void PercDown(MaxHeap H, int p);
void BuildHeap(MaxHeap H);
void test();
void test2();
void test3();
int main(int argc,char *argv[])
{
    cout<<"------------------------------------test1-----------------------------------------------"<<endl;
    test();
    cout<<"------------------------------------test2-----------------------------------------------"<<endl;
	test2();
    cout<<"------------------------------------test3-----------------------------------------------"<<endl;
	test3();
	return 0;
}

MaxHeap create(int maxsize)
{
	MaxHeap h=new HeapNode;
	h->v=(ElementType*)malloc(sizeof(ElementType)*(maxsize+1));
	h->tail=0;
	h->capacity=maxsize;
	h->v[0]=INT_MAX;//有效数据下标从一开始  
	return h;
}


void insert(MaxHeap h,ElementType data)
{
	if(isfull(h))
	{
		cout<<"heap is full!"<<endl;
		return;
	}
	int pos=++h->tail;
	while(data>h->v[pos/2]&&pos>1)  //这里不加pos>1也行因为设置了h->v[0]=MAX_INT
	{
		h->v[pos]=h->v[pos/2];
		pos=pos/2;
	}
	h->v[pos]=data;
}

ElementType DeleteMax(MaxHeap h)
{
	ElementType data=h->v[1];
	ElementType temp=h->v[h->tail--];
	int i=1;
	int j=2*i;
	while(j<=h->tail)
	{	
		if(j<h->tail&&h->v[j]<h->v[j+1])
			j++;
		if(temp>h->v[j]) break;
		h->v[i]=h->v[j];
		i=j;
		j=2*i;
	}
	h->v[i]=temp;
	return data;
}

bool isfull(MaxHeap h)
{
	return h->tail==h->capacity;
}

bool isEmpty(MaxHeap h)
{
	return h->tail==0;
}

void freeheap(MaxHeap h)
{
	delete h->v;
	delete h;
}

ElementType* makemaxheap(ElementType arr[])
{
	int len=arr[0];
	for(int i=len/2;i>0;i--)
	{
		ElementType temp=arr[i];
		int pos=i;
		int index;
		while(1)
		{
			index=2*pos;
			if(index>len) break;
			if(index!=len&&arr[index]<arr[index+1])
				index++;
			if(temp>arr[index]) break;
			arr[pos]=arr[index];
			pos=index;
		}
		arr[pos]=temp;
	}
	return arr;
}

void PercDown(MaxHeap H, int p)
{
    int Parent, Child;
    ElementType temp;
    temp = H->v[p]; /* 取出根结点存放的值 */
    for( Parent=p,Child=2*Parent; Parent*2<=H->tail;) {
        if( (Child<H->tail) && (H->v[Child]<H->v[Child+1]) )
            Child++;  
        if( temp >= H->v[Child] ) break; 
        H->v[Parent] = H->v[Child];
        Parent=Child;
        Child = Parent * 2;
    }
    H->v[Parent] = temp;
}
 
void BuildHeap(MaxHeap H)
{ 
    int i;
    for( i = H->tail/2; i>0; i-- ) //从最后一个非叶子节点开始往上依次构造最大堆
        PercDown( H, i );
}

void test()
{
	int len;
	int* arr;
	FILE *fp=fopen("1.txt","r");
	fscanf(fp,"%d",&len);
	arr=(int*)malloc(sizeof(int)*len);
	for(int i=0;i<len;i++)
	{
		fscanf(fp," %d",&arr[i]);
	}
	fclose(fp);
	MaxHeap myheap=create(len);
	for(int i=0;i<len;i++)
	{
		insert(myheap,arr[i]);
	}
	printf("len=%d\n",len);
	for(int i=0;i<len;i++)
	{		
		printf("%d\t",arr[i]);
		if((i+1)%5==0)
			printf("\n");
	}	
	printf("\n******************************************************\n");
	for(int i=0;i<len;i++)
	{
		printf("%d\t",DeleteMax(myheap));
		if((i+1)%5==0)
			printf("\n");
	}
	printf("\n******************************************************\n");
	freeheap(myheap);
	delete arr;
}

void test2()
{
	MaxHeap myheap;
    myheap=create(7);
    myheap->tail=7;
	for(int i=1;i<=7;i++)
	{
		myheap->v[i]=i;
	}
	BuildHeap(myheap);
	for(int i=1;i<=7;i++)
	{
		cout<<setw(5)<<DeleteMax(myheap);
	}
	cout<<endl;
	freeheap(myheap);
}

void test3()
{
	ElementType* arr=(ElementType*)malloc(sizeof(ElementType)*8);
	arr[0]=7;
	for(int i=1;i<=7;i++)
	{
		arr[i]=i;
	}
	arr=makemaxheap(arr);
	for(int i=1;i<=7;i++)
	{
		cout<<setw(5)<<arr[i];
	}
	cout<<endl;
    delete arr;
}
