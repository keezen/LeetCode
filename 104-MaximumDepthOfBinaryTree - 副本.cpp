/*
104. Maximum Depth of Binary Tree
Easy

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the
root node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
# include <queue>
using namespace std;


template <typename T> ostream & operator<<(ostream &os, pair<T, T> &x)
{
    os << x.first << ',' << x.second;
}


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    // print out a vector
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
        cout << ((i == data.size() - 1) ? eol : sep);
    }
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};


int maxDepthRecur(TreeNode* root)
{
    // max depth of binary tree
    // solution: recursive

    if (root == NULL)
        return 0;

    return max(maxDepthRecur(root->left), maxDepthRecur(root->right)) + 1;
}


int maxDepth(TreeNode* root)
{
    // max depth of binary tree
    // solution: level-order traversal, BFS

    if (root == NULL)
        return 0;

    queue<TreeNode *> q;
    q.push(root);
    int res = 0;

    while (!q.empty())
    {
        int n = q.size();
        while (n--)
        {
            TreeNode *p = q.front();
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
            q.pop();
        }
        res++;
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    int res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = maxDepth(root);
    cout << res << endl;


    myfile.close();
    return 0;
}
