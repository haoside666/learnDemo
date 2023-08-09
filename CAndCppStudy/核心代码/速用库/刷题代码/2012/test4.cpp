#include <stdio.h>
#include <stdlib.h>
typedef struct data
{
    int coef;
    int power;
} Data;

typedef struct Node
{
    Data data;
    struct Node *next;
    Node() {}
    Node(Data data)
    {
        this->data = data;
        this->next = NULL;
    }
    Node(int coef, int power)
    {
        this->data.coef = coef;
        this->data.power = power;
        this->next = NULL;
    }
} Node;
typedef Node *List;

void init(List *head)
{
    (*head) = new Node;
    (*head)->next = NULL;
}
//尾插法
void insertData(List head, Data data)
{
    List temp = new Node;
    temp->data = data;
    temp->next = NULL;
    List p = head;
    while (p->next)
    {
        p = p->next;
    }
    temp->next = p->next;
    p->next = temp;
}

void printList(List head)
{
    List p = head->next;
    while (p)
    {
        printf("%d %d\t", p->data.power, p->data.coef);
        p = p->next;
    }
    printf("\n");
}
void deleteList(List head)
{
    List p, q;
    p = head->next;
    q = head->next;
    while (p)
    {
        q = q->next;
        free(p);
        p = q;
    }
    free(head);
}

List sub(List f, List g)
{
    List head;
    init(&head);
    Node *p = f->next, *q = g->next, *t = head;
    while (p && q)
    {
        if (p->data.power > q->data.power)
        {
            t->next = new Node(p->data);
            t = t->next;
            p = p->next;
        }
        else if (p->data.power < q->data.power)
        {
            t->next = new Node(-q->data.coef, q->data.power);
            t = t->next;
            q = q->next;
        }
        else
        {
            if (p->data.coef != q->data.coef)
            {
                t->next = new Node(p->data.coef - q->data.coef, p->data.power);
                t = t->next;
            }
            p = p->next;
            q = q->next;
        }
    }
    while (p)
    {
        t->next = new Node(p->data);
        t = t->next;
        p = p->next;
    }
    while (q)
    {
        t->next = new Node(q->data);
        t = t->next;
        q = q->next;
    }
    return head;
}

int main(int argc, char *argv[])
{
    List f;
    init(&f);
    Data data;
    data.coef = 1;
    data.power = 5;
    insertData(f, data);
    data.coef = 1;
    data.power = 2;
    insertData(f, data);
    data.coef = -1;
    data.power = 1;
    insertData(f, data);
    data.coef = 4;
    data.power = 0;
    insertData(f, data);
    printList(f);

    List g;
    init(&g);
    data.coef = 2;
    data.power = 7;
    insertData(g, data);
    data.coef = 3;
    data.power = 2;
    insertData(g, data);
    data.coef = -1;
    data.power = 1;
    insertData(g, data);
    data.coef = 1;
    data.power = 0;
    insertData(g, data);
    printList(g);

    List c=sub(f,g);
    printList(c);


    deleteList(f);
    deleteList(g);
    deleteList(c);
    return 0;
}
