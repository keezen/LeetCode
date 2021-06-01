/*
226. Invert Binary Tree
Easy

Given the root of a binary tree, invert the tree, and return its root.

 
Example 1:
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Example 2:
Input: root = [2,1,3]
Output: [2,3,1]

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


TreeNode* invertTreeR(TreeNode* root)
{
    // invert tree level-wise
    // solution: recursive

    if (root == NULL)
        return root;
    if (root->left == NULL && root->right == NULL)
        return root;

    TreeNode *l = root->left;
    TreeNode *r = root->right;
    root->left = invertTreeR(r);
    root->right = invertTreeR(l);

    return root;
}


TreeNode* invertTree(TreeNode* root)
{
    // invert tree level-wise
    // solution: iterative, traversal with stack

    if (root == NULL)
        return root;
    if (root->left == NULL && root->right == NULL)
        return root;

    vector<TreeNode *> st;
    TreeNode *p;
    st.push_back(root);
    while (!st.empty())
    {
        p = st.back();
        st.pop_back();

        swap(p->left, p->right);
        if (p->left != NULL)
            st.push_back(p->left);
        if (p->right != NULL)
            st.push_back(p->right);
    }

    return root;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    TreeNode *res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = invertTree(root);
    // cout << res << endl;
    // PrintVec(res);


    myfile.close();
    return 0;
}
