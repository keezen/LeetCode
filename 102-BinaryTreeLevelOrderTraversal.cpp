/*
102. Binary Tree Level Order Traversal
Medium

Given a binary tree, return the level order traversal of its nodes!
values. (i.e., from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
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


vector<vector<int> > levelOrder(TreeNode* root)
{
    // traverse binary tree in level order
    // solution: queue, pop and visit from head, push all children from tail

    vector<vector<int> > res;
    if (root == NULL)
        return res;

    queue<TreeNode *> q;
    TreeNode *p;
    int n;

    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        vector<int> row;
        while (n--)
        {
            p = q.front(); q.pop();
            row.push_back(p->val);
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        res.push_back(row);
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    vector<vector<int> > res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = levelOrder(root);
    for (int i = 0; i < res.size(); i++)
        PrintVec(res[i]);


    myfile.close();
    return 0;
}
