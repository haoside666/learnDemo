#include <iostream>
using namespace std;
class node
{
public:
    int value;
    node *next;
    node() {}
    node(int value, node *ptr = NULL) : value(value), next(ptr)
    {
    }
};
node *ListInsert(node *first, int data)
{
    if (first->next == NULL)
        return NULL;
    node *p = first;
    while (p->next->next)
    {
        p = p->next;
    }
    node *temp = new node(data, p->next);
    p->next = temp;
    return first;
}

ostream &operator<<(ostream &os, const node *first)
{
    node *p = first->next;
    while (p)
    {
        os << p->value << " ";
        p = p->next;
    }
    os << endl;
    return os;
}

int main(int argc, char *argv[])
{
    node *list = new node;
    list->next = new node(1, NULL);
    cout << list;
    ListInsert(list, 2);
    ListInsert(list, 3);
    ListInsert(list, 4);
    cout << list;
    return 0;
}