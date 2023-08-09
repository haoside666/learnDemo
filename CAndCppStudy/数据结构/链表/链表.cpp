//链表实例01
/*
    ①.用可变数组实现带头结点的链表
    ②.完成最基本的增删改查的操作
    ③.用C++
*/
#include <iostream>
using namespace std;
using ElemType=int;
using Position=int;
typedef struct node
{
	ElemType data;
	struct node* next;
}NODE;
class MyList{
public:
    MyList();
    ~MyList();
    friend ostream& operator<<(ostream& os,const MyList &list);
    //采用尾插法
    void insertData(Position index,ElemType data);
    void deleteData(Position index);
    void updateData(Position index,ElemType data);
    ElemType findData(ElemType data);
	bool findKth(Position index);
public:
    int length;
    NODE* head;
};

MyList::MyList()
{
	this->head=new NODE;
    this->length=0;
	this->head->next=nullptr;
	cout<<"创建链表成功"<<endl;
}
MyList::~MyList()
{
	NODE *p,*q;
	p=head->next;
	q=head->next;
	while(p)
	{	
		q=q->next;
		delete p;	
		p=q;	
	}	
	delete head;
}
void MyList::insertData(Position index,ElemType data)
{
	NODE* temp=new NODE;
	temp->data=data;
	temp->next=nullptr;
	if(index<1||index>this->length+1)
	{
		cerr<<"insert fail"<<endl;
		return;
	}
	NODE* p=head;
	int j=1;
	while(j<index)
	{
		p=p->next;
		j++;
	}
	temp->next=p->next;
	p->next=temp;
	this->length++;
}

void MyList::deleteData(Position index)
{
	if(index<1||index>this->length)
	{
        cerr<<"delete fail"<<endl;
		return;
	}
	NODE *p=head,*q;
	int j=1;
	while(j<index)
	{
		p=p->next;
		j++;
	}
	q=p->next;
	p->next=p->next->next;
	delete q;
	this->length--;
}

bool MyList::findKth(Position index)
{
	if(index<1||index>this->length)
		return -1;
	return 0;
}

void MyList::updateData(Position index,ElemType data)
{
	if(index<1||index>this->length)
	{
        cerr<<"delete fail"<<endl;
		return;
	}
	NODE *p=head->next;
	int j=1;
	while(j<index)
	{
		p=p->next;
		j++;
	}
	p->data=data;
}

int MyList::findData(ElemType data)
{
	int i=1;
	NODE* p=head->next;
	while(p)
	{
		if(p->data==data)
		{
			return i;
		}
		i++;
	}
	return -1;
}

ostream& operator<<(ostream& os,const MyList &list)
{
	NODE *p;
	p=list.head->next;
	os<<"-------------------------"<<endl;
	os<<"开始打印链表"<<endl;
	while(p)
	{	
		os<<p->data<<" ";
		p=p->next;	
	}
	os<<"\n打印链表结束"<<endl;
	os<<"-------------------------"<<endl;
	return os;
}

int main(int argc,char *argv[])
{
	MyList list;
	cout<<"operation:insert 1 1"<<endl;
	list.insertData(1,1);

	cout<<list;
	cout<<"operation:insert 2 2"<<endl;
	cout<<"operation:insert 3 3"<<endl;
	list.insertData(2,2);
	list.insertData(3,3);
	cout<<list;
	cout<<"operation:delete 2"<<endl;
	list.deleteData(2);
	cout<<list;
	cout<<"operation:update 2 666"<<endl;
	list.updateData(2,666);
	cout<<list;
	cout<<"元素1所在链表的位置"<<list.findData(1)<<endl;

	return 0;
}
