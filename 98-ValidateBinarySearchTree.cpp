/*
98. Validate Binary Search Tree
Medium

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true

Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
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


bool isValidBST(TreeNode *root, long long lower, long long upper)
{
    if (root == NULL)
        return true;

    if (root->val >= upper) return false;
    if (root->val <= lower) return false;

    if (!isValidBST(root->left, lower, root->val)) return false;
    if (!isValidBST(root->right, root->val, upper)) return false;

    return true;
}

bool isValidBSTRecur(TreeNode* root)
{
    // whether a binary tree is valid BST
    // solution: recursive, pass limit

    if (root == NULL)
        return true;

    return isValidBST(root, LLONG_MIN, LLONG_MAX);
}


bool isValidBSTPre(TreeNode* root)
{
    // whether a binary tree is valid BST
    // solution: stack, pre-order traversal

    if (root == NULL)
        return true;

    vector<TreeNode *> st;
    vector<long long> lower, upper;
    TreeNode *p;
    long long l, u;

    st.push_back(root);
    lower.push_back(LONG_LONG_MIN);
    upper.push_back(LONG_LONG_MAX);
    while (!st.empty())
    {
        p = st.back(); l = lower.back(); u = upper.back();
        if (p->val >= u || p->val <= l)
            return false;
        st.pop_back(); lower.pop_back(); upper.pop_back();
        if (p->right)
        {
            st.push_back(p->right); lower.push_back(p->val); upper.push_back(u);
        }
        if (p->left)
        {
            st.push_back(p->left); lower.push_back(l); upper.push_back(p->val);
        }
    }

    return true;
}


bool isValidBST(TreeNode* root)
{
    // whether a binary tree is valid BST
    // solution: stack, in-order traversal

    if (root == NULL)
        return true;

    vector<TreeNode *> st;
    TreeNode *p = root;
    long long last = LLONG_MIN;

    while (p != NULL || !st.empty())
    {
        if (p != NULL)
        {
            st.push_back(p);
            p = p->left;
        }
        else
        {
            p = st.back();
            if (p->val <= last)
                return false;
            else
                last = p->val;
            st.pop_back();
            p = p->right;
        }
    }

    return true;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    bool res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = isValidBST(root);
    cout << res << endl;


    myfile.close();
    return 0;
}
