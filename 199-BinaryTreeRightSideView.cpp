/*
199. Binary Tree Right Side View
Medium

Given the root of a binary tree, imagine yourself standing on the
right side of it, return the values of the nodes you can see 
ordered from top to bottom.

 
Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,null,3]
Output: [1,3]

Example 3:
Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
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


vector<int> rightSideView(TreeNode* root)
{
    // right side view of binary tree
    // solution: breadth first search, queue, level-order traversal

    if (root == NULL)
        return vector<int>();

    queue<TreeNode *> q;
    TreeNode *p;
    vector<int> res;
    int i, n;

    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        res.push_back(q.back()->val);
        for (i = 0; i < n; i++)
        {
            p = q.front();
            q.pop();
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    vector<int> res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = rightSideView(root);
    // cout << res << endl;
    PrintVec(res);


    myfile.close();
    return 0;
}
