#include <iostream>
#include <cstdio>
using namespace std;

typedef struct node
{
	char data;
	struct node *next;
} NODE, *STR;

NODE *find(STR s, STR t)
{
	while (s != nullptr && t != nullptr)
	{
		if (s->data == t->data)
		{
			s = s->next;
			t = t->next;
		}
		else
		{
			return s;
		}
	}
	if (s != nullptr)
	{
		return s;
	}
	return nullptr;
}
int length(STR head)
{
	STR p = head;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}
void insertData(STR *phead, int i, char data)
{
	STR temp = (STR)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = NULL;
	STR p = *phead;
	if (i == 1)
	{
		if (*phead == NULL)
			*phead = temp;
		else
		{
			temp->next = *phead;
			*phead = temp;
		}
	}
	else
	{
		if (i < 1 || i > length(p) + 1)
		{
			fprintf(stderr, "insert fail\n");
			return;
		}
		else
		{
			int j = 2;
			while (j < i)
			{
				p = p->next;
				j++;
			}
			temp->next = p->next;
			p->next = temp;
		}
	}
}

void deleteData(STR *head, int i)
{
	STR p = *head;
	STR q = *head;
	int j = 2;
	if (i < 1 || i > length(p))
	{
		fprintf(stderr, "delete fail\n");
		return;
	}
	else if (i == 1)
	{
		p = p->next;
		free(q);
		*head = p;
	}
	else
	{
		while (j < i)
		{
			p = p->next;
			j++;
		}
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
}
void printSTR(STR head)
{
	STR p = head;
	while (p)
	{
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}
void deleteSTR(STR head)
{
	STR p, q;
	p = q = head;
	while (p)
	{
		q = q->next;
		free(p);
		p = q;
	}
}

int main()
{
	STR s = NULL;
	insertData(&s, 1, 'A');
	insertData(&s, 2, 'B');
	insertData(&s, 3, 'C');
	printSTR(s);
	STR t = NULL;
	insertData(&t, 1, 'A');
	insertData(&t, 2, 'B');
	insertData(&t, 3, 'C');
	// insertData(&t, 4, 'D');
	printSTR(t);
	STR pos = find(s, t);
	if(pos!=nullptr)
		printSTR(pos);
	else
		cout<<"nullptr"<<endl;
	return 0;
}
