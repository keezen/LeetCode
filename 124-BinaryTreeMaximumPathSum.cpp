/*
124. Binary Tree Maximum Path Sum
Hard

Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from
some starting node to any node in the tree along the parent-child
connections. The path must contain at least one node and does not
need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


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
    TreeNode *left;
    TreeNode *right;
    int val;
    TreeNode () : val(0), left(nullptr), right(nullptr) {}
    TreeNode (int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode (int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int maxPathSum(TreeNode *root, int &max_path)
{
    // maximum path which ends with root
    // solution: recursive, max_path stores the maximum sum of any
    // path so far

    if (!root)
        return INT_MIN;

    int left = maxPathSum(root->left, max_path);
    int right = maxPathSum(root->right, max_path);

    if (left < 0) left = 0;  // drop negative path
    if (right < 0) right = 0;

    max_path = max(max_path, left + right + root->val);

    return max(left, right) + root->val;
}


int maxPathSum(TreeNode* root)
{
    // maximum sum of any path in the binary tree
    int max_path = INT_MIN;
    maxPathSum(root, max_path);
    return max_path;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    TreeNode *root = NULL;
    root = new TreeNode(-2);
    root->left = new TreeNode(1);
    // root->right = new TreeNode(3);

    int res;
    res = maxPathSum(root);
    cout << res << endl;

    myfile.close();
    return 0;
}
