#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node {
    int Data;
    struct Node *Left,*Right;
}*head = NULL;
Node *New(int d) {
    Node *node = (Node *)malloc(sizeof(Node));
    node -> Data = d;
    node -> Left = node -> Right = NULL;
    return node;
}
Node *ll(Node *node) {
    Node *l = node -> Left;
    node -> Left = l -> Right;
    l -> Right = node;
    return l;
}
Node *rr(Node *node) {
    Node *r = node -> Right;
    node -> Right = r -> Left;
    r -> Left = node;
    return r;
}
Node *lr(Node *node) {
    node -> Left = rr(node -> Left);
    return ll(node);
}
Node *rl(Node *node) {
    node -> Right = ll(node -> Right);
    return rr(node);
}
int max(int a,int b) {
    return a > b ? a : b;
}
int Height(Node *node) {
    return node == NULL ? 0 : max(Height(node -> Left),Height(node -> Right)) + 1;
}
Node* Insert(Node *node,int d) {
    if(node == NULL) {
        node = New(d);
    }
    else if(d < node -> Data) {
        node -> Left = Insert(node -> Left,d);
    }
    else {
        node -> Right = Insert(node -> Right,d);
    }
    if(Height(node -> Left) - Height(node -> Right) == 2) {
        if(d < node -> Left -> Data) {
            node = ll(node);
        }
        else {
            node = lr(node);
        }
    }
    else if(Height(node -> Left) - Height(node -> Right) == -2) {
        if(d > node -> Right -> Data) {
            node = rr(node);
        }
        else {
            node = rl(node);
        }
    }
    return node;
}
int main() {
    int n,d;
    scanf("%d",&n);
    for(int i = 0;i < n;i ++) {
        scanf("%d",&d);
        head = Insert(head,d);
    }
    printf("%d",head -> Data);
    return 0;
}
