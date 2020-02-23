/*
101. Symmetric Tree
Easy

Given a binary tree, check whether it is a mirror of itself
(i.e., symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3


But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3
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


bool isSymmetric(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    if (root1->val != root2->val)
        return false;

    if (!isSymmetric(root1->left, root2->right)) return false;
    if (!isSymmetric(root2->left, root1->right)) return false;

    return true;
}


bool isSymmetricRecur(TreeNode* root)
{
    // whether a binary tree is symmetric
    // solution: recursive, two trees are symmetric

    if (root == NULL)
        return true;

    return isSymmetric(root->left, root->right);
}


bool isSymmetric(TreeNode* root)
{
    // whether a binary tree is symmetric
    // solution: stack, pre-order traversal of two trees in different direction

    if (root == NULL)
        return true;

    vector<TreeNode *> st;
    TreeNode *p1, *p2;

    st.push_back(root);
    st.push_back(root);
    while (!st.empty())
    {
        p1 = st.back(); st.pop_back();
        p2 = st.back(); st.pop_back();
        if (p1 == NULL && p2 == NULL) continue;
        if (p1 == NULL || p2 == NULL || p1->val != p2->val) return false;
        st.push_back(p1->left); st.push_back(p2->right);
        st.push_back(p2->left); st.push_back(p1->right);
    }

    return true;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    bool res;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);

    res = isSymmetric(root);
    cout << res << endl;


    myfile.close();
    return 0;
}
