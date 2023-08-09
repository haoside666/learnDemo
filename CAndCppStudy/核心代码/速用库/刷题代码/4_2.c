#include <stdio.h>
#include <stdlib.h>
typedef struct TNode* AVLTree;
struct TNode {
    int Data;
    AVLTree Left,Right;
};
AVLTree New(int d) {
    AVLTree node = (AVLTree)malloc(sizeof(struct TNode));
    node -> Data = d;
    node -> Left = node -> Right = NULL;
    return node;
}
AVLTree ll(AVLTree node) {
    AVLTree l = node -> Left;
    node -> Left = l -> Right;
    l -> Right = node;
    return l;
}
AVLTree rr(AVLTree node) {
    AVLTree r = node -> Right;
    node -> Right = r -> Left;
    r -> Left = node;
    return r;
}
AVLTree lr(AVLTree node) {
    node -> Left = rr(node -> Left);
    return ll(node);
}
AVLTree rl(AVLTree node) {
    node -> Right = ll(node -> Right);
    return rr(node);
}
int max(int a,int b) {
    return a > b ? a : b;
}
int Height(AVLTree node) {
    return node == NULL ? 0 : max(Height(node -> Left),Height(node -> Right)) + 1;
}
AVLTree Insert(AVLTree node,int d) {
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
    AVLTree head=NULL;
    scanf("%d",&n);
    for(int i = 0;i < n;i ++) {
        scanf("%d",&d);
        head = Insert(head,d);
    }
    printf("%d",head -> Data);
    return 0;
}
