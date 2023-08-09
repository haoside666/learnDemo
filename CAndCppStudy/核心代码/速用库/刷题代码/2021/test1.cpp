#include <iostream>
#include <stack>
#include <list>
#include <queue>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode(int data) : data(data) {}
};
//自底向上
class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight == -1 || rightHeight == -1 || labs(leftHeight - rightHeight) > 1) {
            return -1;
        } else {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }
};
//自顶向下
class Solution2 {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        } else {
            return max(height(root->left), height(root->right)) + 1;
        }
    }
    bool isBalanced(TreeNode* root) {
        if (root == NULL) {
            return true;
        } else {
            return labs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
        }
    }
};


int main()
{
    TreeNode *tree = new TreeNode(3);
    tree->left = new TreeNode(10);
    tree->right = new TreeNode(20);
    tree->left->left = new TreeNode(30);
    tree->left->right = new TreeNode(40);
    tree->left->left->left = new TreeNode(60);
    tree->right->left = new TreeNode(70);
    tree->right->right = new TreeNode(80);
    tree->right->right->left = new TreeNode(100);
    Solution s;
    cout<<"isBalanced:"<<boolalpha<<s.isBalanced(tree)<<endl;
    Solution2 s2;
    cout<<"isBalanced:"<<boolalpha<<s2.isBalanced(tree)<<endl;
    return 0;
}

