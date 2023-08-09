#include <iostream>
#include <vector>
using namespace std;
typedef int ElemType;
// 结点类型定义
typedef struct DulNode
{
	ElemType data;
	struct DulNode* front; // 前驱指针
	struct DulNode* next; // 后继指针
}DulNode, *DulList;
void CreateList(DulList& DL,vector<int>& v)
{
	DulNode *p, *rear;
	DL = new DulNode; // 表头结点，表头结点不存储数据。
	DL->next = NULL;
	DL->front = NULL;
	rear = DL; // 表尾指针
	for(int i=0;i<v.size();i++)
	{
		p = new DulNode; // 生成新的结点
		p->data = v[i];
		p->next = rear->next; // 这里填NULL也可以。
		p->front = rear;
		rear->next = p;
		rear = p; // 表尾指针更新为最新元素
	}
}
void DoubleWayBubbleSort(DulList& DL)
{// 对存储在带头结点的双向链表DL中的元素进行双向起泡排序
	int flag = 1; // 设标记，可用于提前结束冒泡过程
	DulNode* head = DL; // 双向链表表头，算法过程中是向下起泡的开始结点
	DulNode* tail = NULL; // 双向链表表尾，算法过程中是向上起泡的开始结点
	while (flag)
	{
		DulNode* p = head->next; // 工作指针
		flag = 0; // 假设本趟无交换，用于提前停止
		while (p->next != tail)
		{// 向下起泡
			if (p->data > p->next->data) {
				flag = 1; // 此趟有交换
				DulNode* tmp = p->next; // tmp用于暂时指代将要与p交换的结点
				p->next = tmp->next; // p的后继结点指向tmp的后继结点
				if (tmp->next != NULL) tmp->next->front = p; // 该后继结点的前驱指针指向p
				p->front->next = tmp; // p的前驱结点的后继指针指向tmp
				// p的前驱结点变为tmp的前驱结点，p变为tmp的后继结点
				tmp->front = p->front;
				p->front = tmp;
				tmp->next = p;
				// p = p->next; 这里是因为在交换的过程中p已经移动到下一个位置了
			}
			else {
				p = p->next; // 指向下一结点
			}
		}
		tail = p; // 准备向上起泡
		p = tail->front;
		while (flag && p->front != head)
		{ // 向上起泡
			if (p->data < p->front->data)
			{
				DulNode* tmp = p->front;
				p->front = tmp->front;
				// if (tmp->front != NULL) 
					tmp->front->next = p;
				p->next->front = tmp;
				tmp->next = p->next;
				p->next = tmp;
				tmp->front = p;
			}
			else {
				p = p->front;
			}
		}
		head = p; // 为下一次向下起泡作准备
	}

}

void PrintList(DulList DL)
{
	DulNode* p = DL->next;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout<<endl;
}
int main(void)
{
	vector<int> arr = {4, 2, 5, 8, 9, 1};
	DulList D;
	CreateList(D, arr); // 建表
	cout << "冒泡排序前：";
	PrintList(D); // 打印链表测试生成是否正确
	cout << endl;
	DoubleWayBubbleSort(D);
	cout << "冒泡排序后：";
	PrintList(D);
	return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;
// typedef int ElemType;
// // 结点类型定义
// struct Node
// {
// 	ElemType data;
// 	struct Node *front; // 前驱指针
// 	struct Node *next;	// 后继指针
// };
// typedef Node *PNode;

// class DoubleList
// {
// public:
// 	DoubleList()
// 	{
// 		head = new Node;
// 		head->data = 0;
// 		head->next = head->front = nullptr;
// 	}
// 	void CreatList(vector<int> &v)
// 	{
// 		PNode p,rear=head;
// 		for (int i = 0; i < v.size(); i++)
// 		{
// 			p = new Node;
// 			p->data = v[i];
// 			p->next = rear->next;
// 			p->front = rear;
// 			rear->next = p;
// 			rear = p; // 表尾指针更新为最新元素
// 		}
// 	}

// 	void DoubleWayBubbleSort()
// 	{
// 		PNode start = head->next;
// 		PNode end = nullptr, start_temp, end_temp, temp;
// 		if (!start)
// 			return;
// 		while (start != end) //还未到末尾
// 		{
// 			start_temp = start;
// 			end_temp = end;
// 			while (start_temp->next != end_temp)
// 			{
// 				if (start_temp->data > start_temp->next->data)
// 				{
// 					//换链法
// 					temp = start_temp->next;

// 					start_temp->front->next = temp;
// 					temp->front = start_temp->front;
// 					start_temp->next = temp->next;
// 					if(temp->next!=nullptr) temp->next->front = start_temp;
// 					temp->next = start_temp;
// 					start_temp->front = temp;
// 					//改数据法
// 					// ElemType data_temp1=start_temp->data;
// 					// ElemType data_temp2=start_temp->next->data;
// 					// start_temp->data=data_temp2;
// 					// start_temp->next->data=data_temp1;
// 				}
// 				else
// 				{
// 					start_temp = start_temp->next;
// 				}
// 			}
// 			end = start_temp;
// 			end_temp = end->front;
// 			while (end_temp->front != head)
// 			{
// 				if (end_temp->data > end_temp->front->data)
// 				{
// 					//换链法
// 					temp = end_temp->front;
// 					end_temp->next->front = temp;
// 					temp->next = end_temp->next;
// 					end_temp->front = temp->front;
// 					if(temp->front!=nullptr) temp->front->next = end_temp;
// 					temp->front = end_temp;
// 					end_temp->next = temp;
// 				}
// 				else
// 				{
// 					end_temp = end_temp->front;
// 				}
// 			}
// 		}
// 	}

// 	friend ostream &operator<<(ostream &out, const DoubleList &dList);

// private:
// 	PNode head;
// };
// ostream &operator<<(ostream &out, const DoubleList &dList)
// {
// 	PNode p = dList.head->next;
// 	while (p)
// 	{
// 		out << p->data << "  ";
// 		p = p->next;
// 	}
// 	cout << endl;
// 	return out;
// }
// int main(void)
// {
// 	vector<int> arr = {4, 2, 5, 8, 9, 1};
// 	DoubleList dList;
// 	dList.CreatList(arr);
// 	cout << "冒泡排序前:" << endl;
// 	cout << dList << endl; // 打印链表测试生成是否正确
// 	dList.DoubleWayBubbleSort();
// 	cout << "冒泡排序后:" << endl;
// 	cout << dList << endl;
// 	return 0;
// }
