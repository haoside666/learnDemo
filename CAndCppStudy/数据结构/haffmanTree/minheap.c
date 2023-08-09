#include "union.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
MinHeap create(int maxsize)
{
	MinHeap h=malloc(sizeof(struct HeapNode));
	h->data=malloc(sizeof(ElementType)*(maxsize+1));
	h->size=0;
	h->capacity=maxsize;
	h->data[0]=(malloc)(sizeof(struct TreeNode));
	h->data[0]->weight=INT_MIN;
	return h;
}


void insert(MinHeap h,ElementType data)
{
	if(isfull(h))
	{
		printf("heap is full!\n");
		return;
	}
	int pos=++h->size;
	while(data->weight<h->data[pos/2]->weight)
	{
		h->data[pos]=h->data[pos/2];
		pos=pos/2;
	}
	h->data[pos]=data;
}

ElementType DeleteMin(MinHeap h)
{
	ElementType data=h->data[1];
	ElementType temp=h->data[h->size--];
	int pos=1;
	int index;
	while(1)
	{
		index=2*pos;
		if(index>h->size) break;
		if(index!=h->size&&h->data[index]->weight>h->data[index+1]->weight)
			index++;
		if(temp->weight<h->data[index]->weight) break;
		h->data[pos]=h->data[index];
		pos=index;
	}
	h->data[pos]=temp;
	return data;
}

bool isfull(MinHeap h)
{
	return h->size==h->capacity;
}

bool isEmpty(MinHeap h)
{
	return h->size==0;
}

void freeheap(MinHeap h)
{
	for(int i=0;i<=h->size;i++)
	{
		free(h->data[i]);
	}
	free(h->data);
	free(h);
}

void PercDown(MinHeap H, int p)
{
    int Parent, Child;
    ElementType X;
 
    X = H->data[p]; 
    for( Parent=p; Parent*2<=H->size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=H->size) && (H->data[Child]->weight>H->data[Child+1]->weight) )
            Child++;  
        if( X->weight <= H->data[Child]->weight ) break; 
        else  
            H->data[Parent] = H->data[Child];
    }
    H->data[Parent] = X;
}
 
void BuildHeap(MinHeap H)
{ 
    int i;
    for( i = H->size/2; i>0; i-- )
        PercDown( H, i );
}

