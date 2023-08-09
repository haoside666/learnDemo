#include <iostream>
#include <queue>
using namespace std;

class BinNode
{
public:
    BinNode *left;
    BinNode *right;
    int data;
    BinNode() : left(NULL), right(NULL) {}
};

void LevelorderTraversal(BinNode*root)
{
    if (root == NULL)
        return;
    queue<BinNode *> que;
    BinNode *temp;
    que.push(root);
    while (!que.empty())
    {
        temp = que.front();
        que.pop();
        cout << temp->data << " ";
        if (temp->left)
        {
            que.push(temp->left);
        }
        if (temp->right)
        {
            que.push(temp->right);
        }
    }
    cout << endl;
}
BinNode *BST_Insert(BinNode *root, int item);
int main(int argc, char *argv[])
{
    BinNode *root;
    root = BST_Insert(root, 40);
    BST_Insert(root, 20);
    BST_Insert(root, 30);
    BST_Insert(root, 50);
    BST_Insert(root, 25);
    BST_Insert(root, 60);
    LevelorderTraversal(root);
    return 0;
}

BinNode *BST_Insert(BinNode *root, int item)
{
    if (root == NULL)
    {
        root = new BinNode;
        root->data = item;
        root->left = root->right = NULL;
    }
    else
    {
        if (item > root->data)
        {
            root->right=BST_Insert(root->right, item);
        }
        else
        {
            root->left=BST_Insert(root->left, item);
        }
    }
    return root;
}
