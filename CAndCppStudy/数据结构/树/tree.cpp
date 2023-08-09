#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
template <typename T>
class TreeNode
{
private:
	T data;	
public:
	vector<TreeNode*> child;
	TreeNode(T data)
	{
		this->data = data;
	}

	T getData()
	{
		return data;
	}

	void insert(TreeNode<T>* node)
	{
		child.push_back(node);
	}


	void out()
	{
		_out(this);  
	}
private:
	void _out(TreeNode<T> *node)
	{
		cout << node->getData() << " ";
		if (node->child.empty())
			return;	
		for (int i = 0; i < node->child.size(); i++)
		{				
			_out(node->child[i]);		
		}
	}
	
};

void test()
{
	TreeNode<int> *tree = new TreeNode<int>(10);
	TreeNode<int> *tree2 = new TreeNode<int>(15);
	tree->insert(tree2);

	TreeNode<int>*tree3 = new TreeNode<int>(48);
	TreeNode<int>*tree4 = new TreeNode<int>(59);
	TreeNode<int>*tree5 = new TreeNode<int>(12);

	tree2->insert(tree3);
	tree2->insert(tree4);
	tree2->insert(tree5);

	tree->out();
}

class BinTreeNode
{
public:
	int data;
	BinTreeNode *left=nullptr;  
	BinTreeNode *right=nullptr;
	BinTreeNode(int data) :data(data){}
};

class BinnaryTree
{
public:
	BinTreeNode *root;
	BinnaryTree(BinTreeNode *node)
	{
		if (node!=nullptr)
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
		return _getDepth(root);
	}
	int size()
	{
		
	}

	
	void perOrder()
	{
		_perOrder(root);
	}
	
	void perOder_no()
	{
		stack<BinTreeNode*> sta;
		sta.push(root);
		while (!sta.empty())
		{
			BinTreeNode *temp = sta.top(); 
			sta.pop();
			cout << temp->data<<endl; 
			if (temp->right)
			{
				sta.push(temp->right);
			}
			if (temp->left)
			{
				sta.push(temp->left);
			}
		}
	}
	
	void in_order()
	{
		in_order(root);
	}
	
	void postorder()
	{
		postorder(root);
	}

private:
	int _getDepth(BinTreeNode *node)
	{
		if (!node)
		{
			return -1;
		}
		int left = _getDepth(node->left) + 1;
		int right = _getDepth(node->right) + 1;
		return left > right ? left : right;
	}

	void _perOrder(BinTreeNode *node)
	{
		if (node)
		{
			cout << node->data << endl; 
			_perOrder(node->left); 
			_perOrder(node->right); 
		}
	}

	void in_order(BinTreeNode *node)
	{

		if (node)
		{			
			in_order(node->left); 
			cout << node->data << endl; 
			in_order(node->right); 
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
	BinTreeNode *tree =new BinTreeNode(3);
	tree->left = new BinTreeNode(10);
	tree->right = new BinTreeNode(20);
	tree->left->left = new BinTreeNode(30);
	tree->left->right = new BinTreeNode(60);

	//BinTreeNode *Tree = new BinTreeNode(3);
	BinnaryTree bt(tree);
	cout <<"depth:"<< bt.getDepth() << endl;
	cout << "per:" << endl;
	bt.perOrder();
	cout << "no-per:" << endl;	
	bt.perOder_no();
	cout << "zhong." << endl;
	bt.in_order();
	cout << "post:" << endl;
	bt.postorder();
}

int main()
{
	test2();
	return 0;
}
