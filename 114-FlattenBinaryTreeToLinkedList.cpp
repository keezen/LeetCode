/*
114. Flatten Binary Tree to Linked List
Medium

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
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


void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}


void flattenRightmost(TreeNode* root)
{
    // flatten binary tree to linked list
    // solution: pre-order traversal, find rightmost node of left sub-tree

    TreeNode *q;
    while(root)
    {
        if (root->left && root->right)  // left and right sub-tree
        {
            // find rightmost node of left sub-tree
            q = root->left;
            while(q->right)
                q = q->right;

            // make rightmost node to parent of right sub-tree
            q->right = root->right;
        }

        if (root->left)  // only left sub-tree
            root->right = root->left;

        root->left = NULL;
        root = root->right;
    }
}


void flattenST(TreeNode* root)
{
    // flatten binary tree to linked list
    // solution: pre-order traversal, stack

    if (!root)
        return;

    vector<TreeNode *> st;
    TreeNode *p, *prev = NULL;
    st.push_back(root);
    while (!st.empty())
    {
        p = st.back(); st.pop_back();

        if (p->right)
            st.push_back(p->right);
        if (p->left)
            st.push_back(p->left);

        if (prev)
        {
            prev->right = p; prev = p;
        }
        else
            prev = p;
        prev->left = NULL;
    }
}


TreeNode* flattenR(TreeNode *root)
{
    if (!root)
        return root;

    if (!(root->left) && !(root->right))
        return root;

    TreeNode *left = flattenR(root->left);
    TreeNode *right = flattenR(root->right);
    if (root->left)
    {
        left->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }

    return right ? right : left;
}


void flatten(TreeNode* root)
{
    // flatten binary tree to linked list
    // solution: pre-order traversal, recursive

    if (!root)
        return;

    flattenR(root);
}



int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);

    preorder(root); cout << endl;
    flatten(root);

    for(TreeNode *p = root; p != NULL; p = p->right)
        cout << p->val << ' ';
    cout << endl;


    myfile.close();
    return 0;
}
