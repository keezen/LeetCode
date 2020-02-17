/*
94. Binary Tree Inorder Traversal
Medium

Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
Follow up: Recursive solution is trivial, could you do it iteratively?
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


vector<int> inorderTraversalStack(TreeNode* root)
{
    // in-order traversal of tree
    // solution: stack, non-empty pointer, push, move left;
    // empty pointer, visit and pop top, move right;

    vector<int> res;
    TreeNode *p;
    vector<TreeNode *> st;

    p = root;
    while (!st.empty() || p != NULL)
    {
        if (p != NULL)  // left not traversed
        {
            st.push_back(p);
            p = p->left;
        }
        else  // left traversal finish
        {
            res.push_back(st.back()->val);
            p = st.back()->right;
            st.pop_back();
        }
    }

    return res;
}


vector<int> inorderTraversal(TreeNode* root)
{
    // in-order traversal of tree
    // solution: morris traversal and threaded binary tree,
    // while current is not null,
    // if left is empty, visit current, move right;
    // if left is not empty, make current right node of rightmost node of
    // left sub-tree, move left.

    vector<int> res;
    TreeNode *p, *q, *t;

    p = root;
    while (p != NULL)
    {
        if (p->left == NULL)  // left empty
        {
            res.push_back(p->val);
            p = p->right;
        }
        else  // left no empty
        {
            // find rightmost node of left sub-tree, make current node become its
            // right child
            for (q = p->left; q->right != NULL; q = q->right) ;
            q->right = p;
            t = p->left; p->left = NULL; p = t;
        }
    }

    return res;
}



int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<int> res;

    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    res = inorderTraversal(root);

    PrintVec(res);

    myfile.close();
    return 0;
}
