#include <iostream>
#include <stack>
#include <list>
#include <queue>
using namespace std;

class BinTreeNode
{
public:
    int data;
    BinTreeNode *left = nullptr;
    BinTreeNode *right = nullptr;
    BinTreeNode(int data) : data(data) {}
};

class BinnaryTree
{
public:
    BinTreeNode *root;
    BinnaryTree(BinTreeNode *node)
    {
        if (node != nullptr)
        {
            this->root = node;
        }
        else
        {
            throw nullptr;
        }
    }

    //双栈法
    void postOrder_no()
    {
        if (root == nullptr)
            return;
        stack<int> result;
        stack<BinTreeNode *> sta;
        sta.push(root);
        while (!sta.empty())
        {
            BinTreeNode *temp = sta.top();
            sta.pop();
            result.push(temp->data);
            if (temp->left)
            {
                sta.push(temp->left);
            }
            if (temp->right)
            {
                sta.push(temp->right);
            }
        }

        while (!result.empty())
        {
            cout << result.top() << " ";
            result.pop();
        }
        cout << endl;
    }
    void postorder()
    {
        postorder(root);
    }
    void postorder(BinTreeNode *node)
    {
        if (node)
        {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << endl;
        }
    }

    
};

void test2()
{
    BinTreeNode *tree = new BinTreeNode(3);
    tree->left = new BinTreeNode(10);
    tree->right = new BinTreeNode(20);
    tree->left->left = new BinTreeNode(30);
    tree->left->right = new BinTreeNode(60);
    tree->right->left = new BinTreeNode(70);
    tree->right->right = new BinTreeNode(80);
    tree->right->right->left = new BinTreeNode(100);

    //BinTreeNode *Tree = new BinTreeNode(3);
    BinnaryTree bt(tree);
    cout << "post:" << endl;
    bt.postorder();
    cout << "post-in:" << endl;
    bt.postOrder_no();
}

int main()
{
    test2();
    return 0;
}
