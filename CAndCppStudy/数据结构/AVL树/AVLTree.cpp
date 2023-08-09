#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
namespace DrawTree
{
#define lChild left  //使用前将 l_child_ 更换为 自己树节点的左孩子的名字
#define rChild right  //使用前将 r_child_ 更换为 自己树节点的右孩子的名字
#define MAXN (1000)      //这棵树的节点上限
#define PERID (2)        //打印两个节点的横坐标间隔
    int SUM;  //统计当前遍历到第几个节点

    // 将光标移动到 (X,Y)
    std::string AXIS(int X, int Y) {
        std::stringstream ss;
        ss << "\033[" << Y << ";" << X << "H";
        return ss.str();
    }

    struct DrawNode {
        int x, y, dataSize;
    }axisArray[MAXN];


    //计算节点数据输出的长度
    template <typename TreePtr>
    int dataSize(TreePtr const& root) {
        std::stringstream ss;
        //对应buildDrawTree中的打印，对应树结点的数据
        ss << root->data << "/" << root->height;
        return (ss.str()).length();
    }

    //中序遍历, 从左往右画节点(不连线)
    //横坐标通过全局变量SUM和上一个节点数据的输出长度算出
    //纵坐标通过递归深度判断
    //PERID 是两个节点间隔长度
    template <typename TreePtr>
    void buildDrawTree(TreePtr const& root, int deep) {
        if (!root) return;  //判断空节点,如果你的节点判空和我不一样,这里也要改, 比如我之前的判断空节点是(root->height_== -1).

        if (root->lChild)  buildDrawTree(root->lChild, deep + 1);

        axisArray[SUM] = { axisArray[SUM - 1].x + axisArray[SUM - 1].dataSize + PERID, deep, dataSize(root) };
        std::cout << AXIS(axisArray[SUM].x, axisArray[SUM].y) << root->data << "/" << root->height;
        ++SUM;

        if (root->rChild)  buildDrawTree(root->rChild, deep + 1);
    }

    template <typename TreePtr>
    void Draw(TreePtr const& t) {  //画树函数
        system("cls"); //清屏
        SUM = 1;
        int maxy = 0;

        buildDrawTree<TreePtr>(t, 2);   //每个结点画出来

        //画节点间连线,因为画的节点不会太多,所以就写了n^2的算法,比较好实现
        //每个节点只有一个父节点,所以画出每个节点和自己父节点的连线即可
        for (int i = 1; i < SUM; i++) {
            //x,y是子节点的坐标,p是父节点的axisArray数组的下标, px,py是父节点的坐标;
            int x = axisArray[i].x, y = axisArray[i].y, p = 0, px = 0, py = y - 1;

            if (y == 1) continue; // 根结点没有父节点,跳过

            for (int j = 1; j < SUM; j++) {  //循环找父节点
                if (i == j) continue;
                if ((!p || abs(axisArray[j].x - x) < abs(px - x)) && axisArray[j].y + 1 == y)
                    p = j, px = axisArray[j].x;
            }

            int s = (2 * x + axisArray[i].dataSize) >> 1;
            std::cout << AXIS(s, py) << '+';
            if (s < px)
                for (int i = s + 1; i < px; i++) std::cout << AXIS(i, py) << '-';
            else
                for (int i = px + axisArray[p].dataSize; i < s; i++) std::cout << AXIS(i, py) << '-';
            maxy = std::max(maxy, y);
        }
        std::cout << AXIS(1, maxy + 1);  //打印完把光标移到最下边.
    }
}
struct TreeNode
{
	int data;
	int height;
	TreeNode *left, *right;
	TreeNode(){}
	TreeNode(int data):data(data),height(0),left(NULL),right(NULL)
	{

	}
};
// //层序遍历
// void LevelorderTraversal(TreeNode *root)
// {
// 	int m=1;
// 	if (root == NULL)
// 		return;
// 	queue<TreeNode *> que;
// 	TreeNode *temp;
// 	que.push(root);
// 	while (!que.empty())
// 	{
// 		m--;
// 		temp = que.front();
// 		que.pop();
// 		cout << temp->data << " ";
// 		if (temp->left)
// 		{
// 			que.push(temp->left);
// 		}
// 		if (temp->right)
// 		{
// 			que.push(temp->right);
// 		}
// 		if(m==0)
//         {
//             cout<<endl;
//             m=que.size();
//         }
// 	}
// 	cout << endl;
// 	cout<<"-------------------------------------"<<endl;
// }
//递归获取高度
int getHeight(TreeNode *root)
{
	if (root==NULL)//为空返回-1
		return -1;
	return root->height;
}
//LL型，右旋单旋
TreeNode *LL(TreeNode *&root)
{
	TreeNode *leftNode = root->left;
	root->left = leftNode->right;
	leftNode->right = root;
	root = leftNode;
	root->right->height = max(getHeight(root->right->left), getHeight(root->right->right)) + 1;
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	//可能为空，但不为空要重新判断高度
	if (root->left)
		root->left->height = max(getHeight(root->left->left), getHeight(root->left->right)) + 1;
	return root;
}
//RR型，左旋单旋
TreeNode *RR(TreeNode *&root)
{
	TreeNode *rightNode = root->right;
	root->right = rightNode->left;
	rightNode->left = root;
	root = rightNode;
	root->left->height = max(getHeight(root->left->left), getHeight(root->left->right)) + 1;
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	//可能为空，但不为空要重新判断高度
	if (root->right)
		root->right->height = max(getHeight(root->right->left), getHeight(root->right->right)) + 1;
	return root;
}
//LR型，先对左子树右旋再左旋
TreeNode *LR(TreeNode *&root)
{
	RR(root->left);
	return LL(root);
}
//RL型，先对右子树左旋再右旋
TreeNode *RL(TreeNode *&root)
{
	LL(root->right);
	return RR(root);
}
//插入叶子结点，递归
//注意使用指针的引用
void insert(int data, TreeNode *&root)
{
	//如果为空，即找到了叶子结点的位置，分配空间
	if (!root)
	{
		root = new TreeNode(data);
	}
	//如果数字比当前结点的值小，即进入当前结点的左子树继续判断
	else if (data < root->data)
	{
		insert(data, root->left);
		//递归出来后，要判断平衡因子，决定是否调平衡
		if (getHeight(root->left) - getHeight(root->right) == 2)
		{
			//如果上面递归是进入了左子树的左子树，则是LL型
			if (data < root->left->data)
				root = LL(root);
			//如果进入左子树的右子树，则是LR型
			else
				root = LR(root);
		}
	}
	//如果数字比当前节点的值大，即进入当前节点的右子树继续判断
	else if (data > root->data)
	{
		insert(data, root->right);
		//递归出来后，要判断平衡因子，决定是否调平衡
		if (getHeight(root->left) - getHeight(root->right) == -2)
		{
			//如果上面递归是进入了右子树的右子树，则是RR型
			if (data > root->right->data)
				root = RR(root);
			//如果进入右子树的左子树，则是RL型
			else
				root = RL(root);
		}
	}
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
}

void createTree(vector<int> v, TreeNode *&pRoot)
{
	for (int i = 0; i < v.size(); i++)
	{
		insert(v[i], pRoot);
		DrawTree::Draw(pRoot);
		system("pause");
	}
	//层序遍历，平衡二叉树是特殊的二叉排序树
}
/*


*/
int main()
{
	vector<int> v = {49, 38, 65, 97, 76, 13, 27};
	TreeNode *pRoot = NULL;
	createTree(v, pRoot);
	return 0;
}