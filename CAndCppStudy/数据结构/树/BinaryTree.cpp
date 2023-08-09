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

    int getDepth()
    {
        return getDepth(root);
    }
    void perOrder()
    {
        perOrder(root);
    }

    void perOder_no()
    {
        if (root == nullptr)
            return;
        stack<BinTreeNode *> sta;
        sta.push(root);
        while (!sta.empty())
        {
            BinTreeNode *temp = sta.top();
            sta.pop();
            cout << temp->data << " ";
            if (temp->right)
            {
                sta.push(temp->right);
            }
            if (temp->left)
            {
                sta.push(temp->left);
            }
        }
        cout << endl;
    }

    void inOder_no()
    {
        if (root == nullptr)
            return;
        BinTreeNode *cur = root;
        stack<BinTreeNode *> sta;
        while (cur != nullptr || !sta.empty())
        {
            if (cur != nullptr)
            {
                sta.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = sta.top();
                sta.pop();
                cout << cur->data << "  ";
                cur = cur->right;
            }
        }
        cout << endl;
    }

    void inOrder()
    {
        inOrder(root);
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

    bool isCompleteTree()
    {
        if(root==nullptr) return true; //空树也算满二叉树
        queue<BinTreeNode*> que;
        BinTreeNode *temp;
        bool flags=false;
        que.push(root);
        while (!que.empty())
        {
            temp = que.front();
            que.pop();
            // if(flags&&(temp->left||temp->left))
            //     return false;
            if (temp->left)
            {
                if(flags)
                    return false;
                que.push(temp->left);
            }else{
                flags=true;
            }
            if (temp->right)
            {
                if(flags)
                    return false;
                que.push(temp->right);
            }else{
                flags=true;
            }
        }
        return true;
    }

    void LevelorderTraversal()
    {
        if (root == NULL)
            return;
        queue<BinTreeNode*> que;
        BinTreeNode *temp;
        que.push(root);
        while (!que.empty())
        {
            temp = que.front();
            que.pop();
            cout<<temp->data<<" ";
            if (temp->left)
            {
                que.push(temp->left);
            }
            if (temp->right)
            {
                que.push(temp->right);
            }
        }
        cout<<endl;
    }
    
    int calcnum(BinTreeNode *root)
    {
        if(!root) return 0;
        return calcnum(root->left)+calcnum(root->right)+1; 
    }

    BinTreeNode* invertTree(BinTreeNode* root){
        if(!root) return nullptr;
        BinTreeNode *temp=root->left;
        root->left=invertTree(root->right);
        root->right=invertTree(temp);
        return root;
    }
private:
    int getDepth(BinTreeNode *node)
    {
        if (!node)
        {
            return 0;
        }
        int left = getDepth(node->left) + 1;
        int right = getDepth(node->right) + 1;
        return left > right ? left : right;
    }

    void perOrder(BinTreeNode *node)
    {
        if (node)
        {
            cout << node->data << endl;
            perOrder(node->left);
            perOrder(node->right);
        }
    }

    void inOrder(BinTreeNode *node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << node->data << endl;
            inOrder(node->right);
        }
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
    cout << "depth:(根节点算第一层)" << bt.getDepth() << endl;
    cout << "per:" << endl;
    bt.perOrder();
    cout << "no-per:" << endl;
    bt.perOder_no();
    cout << "in:" << endl;
    bt.inOrder();
    cout << "no-in:" << endl;
    bt.inOder_no();
    cout << "post:" << endl;
    bt.postorder();
    cout << "post-in:" << endl;
    bt.postOrder_no();
    cout<<"Levelorder:"<<endl;
    bt.LevelorderTraversal();

    cout<<"isCompleteTree:"<<boolalpha<<bt.isCompleteTree()<<endl;

    cout<<"nodeNumber:"<<bt.calcnum(bt.root)<<endl;
    
    bt.invertTree(bt.root);
    cout<<"invertTree after:"<<endl;
    bt.LevelorderTraversal();
}

int main()
{
    test2();
    return 0;
}
