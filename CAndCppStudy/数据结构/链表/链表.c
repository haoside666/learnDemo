#include <stdio.h>
#include <stdlib.h>
typedef struct data
{ 
    int coef;//系数
    int expo;//指数
}DATA;
typedef struct LNode* PtrToLNode;
struct LNode
{
    DATA data;
    PtrToLNode next;
};

struct headlist
{
    PtrToLNode front;
    PtrToLNode rear;
};
typedef struct headlist* List;

List CreateList();
void insertData(List mylist,DATA data);
List BuildList();
void printList(List mylist);
void freeList(List mylist);
void freeList2(List mylist);

List ListAdd(List list1,List list2);
List ListMul(List list1,List list2);

int main(int argc,char *argv[])
{
    List list1,list2,addlist,mullist;
    list1=BuildList();
    list2=BuildList();
    mullist=ListMul(list1,list2);
    addlist=ListAdd(list1,list2);
    printList(mullist);
    printList(addlist);

    freeList(list1);
    freeList(list2);
    freeList(addlist);
    freeList(mullist);
    return 0;
}
List CreateList()
{
    List mylist=malloc(sizeof(struct headlist));
    mylist->rear=mylist->front=NULL;
    return mylist;
}
void insertData(List mylist,DATA data)
{
    PtrToLNode temp=malloc(sizeof(struct LNode));
    temp->data=data;
    temp->next=NULL;
    if(mylist->rear==NULL)
    {       
        mylist->front=mylist->rear=temp;
    }else
    {
       mylist->rear->next=temp;
       mylist->rear=temp;
    }   
}
List BuildList()
{
	int len;
    List mylist;
    DATA data;
    mylist=CreateList();
    scanf("%d",&len);
    for(int i=0;i<len;i++)
    {
        scanf("%d %d",&data.coef,&data.expo);
        insertData(mylist,data);
    }
    return mylist;
}
void printList(List mylist)
{
    int flags=0;
    PtrToLNode p=mylist->front;
    if(p==NULL)
    {
        printf("0 0\n");
    }else
    {       
        while(p!=NULL)
        {
            if(!flags)
                flags=1;
            else
                printf(" ");
            printf("%d %d",p->data.coef,p->data.expo);
            p=p->next;
        }
        printf("\n");
    }
    
}
void freeList(List mylist)
{
    PtrToLNode p=mylist->front;
    PtrToLNode q=mylist->front;
    while(p!=NULL)
    {
        q=q->next;
        free(p);
        p=q;
    }
    free(mylist);//释放头结点
}

void freeList2(List mylist)
{
    PtrToLNode p=mylist->front;
    PtrToLNode q=mylist->front;
    while(p!=NULL)
    {
        q=q->next;
        free(p);
        p=q;
    }
    mylist->front=mylist->rear=NULL;
}
List ListAdd(List list1,List list2)
{
    List addlist=CreateList();//创建一个空链表
    PtrToLNode p1=list1->front;
    PtrToLNode p2=list2->front;
    DATA temp;
    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->data.expo>p2->data.expo)
        {
            insertData(addlist,p1->data);
            p1=p1->next;
        }else if(p1->data.expo<p2->data.expo)
        {
            insertData(addlist,p2->data);
            p2=p2->next;  
        }else
        {
            temp.coef=p1->data.coef+p2->data.coef;
            if(temp.coef!=0)
            {
                temp.expo=p1->data.expo;
                insertData(addlist,temp);           
            }
			p1=p1->next;
            p2=p2->next;
        }
    }
    while(p1!=NULL)
    {
        insertData(addlist,p1->data);
        p1=p1->next;
    }
    while(p2!=NULL)
    {
        insertData(addlist,p2->data);
        p2=p2->next;
    }   
    return addlist;
}
List ListMul(List list1,List list2)
{
    List mullist=CreateList();//创建一个空链表 
    List item=CreateList();//创建一个空链表 
	List p;
    PtrToLNode p1;
    PtrToLNode p2;
    DATA temp;
    p1=list1->front;
    while(p1)
    {       
        p2=list2->front;
        while(p2)
        {
            temp.coef=p1->data.coef*p2->data.coef;
            if(temp.coef!=0)
            {
                temp.expo=p1->data.expo+p2->data.expo;
                insertData(item,temp);
            }
            p2=p2->next;
        }
		p=mullist;
        mullist=ListAdd(mullist,item);
		freeList(p);
        freeList2(item);
        p1=p1->next;
    }
    free(item);
    return mullist;
}
