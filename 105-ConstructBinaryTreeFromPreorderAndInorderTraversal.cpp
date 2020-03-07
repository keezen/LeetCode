/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Medium

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
# include <queue>
# include <map>
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


vector<int> inorderTraversal(TreeNode* root)
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


TreeNode *buildTree(vector<int>& pre, int lp, int rp, vector<int>& in, int li, int ri)
{
    if (rp - lp != ri - li || rp - lp < 0 || lp < 0 || rp >= pre.size() || li < 0 || ri >= in.size())
        return NULL;

    if (lp == rp && pre[lp] == in[li])
        return new TreeNode(pre[lp]);

    int root;
    for (root = li; root <= ri; root++)
        if (in[root] == pre[lp])
            break;

    TreeNode *res = new TreeNode(pre[lp]);
    res->left = buildTree(pre, lp+1, lp+root-li, in, li, root-1);
    res->right = buildTree(pre, rp-ri+root+1, rp, in, root+1, ri);

    return res;
}


TreeNode* buildTreeRecur(vector<int>& preorder, vector<int>& inorder)
{
    // build binary tree from pre-order and in-order traversal
    // solution: recursive, find root in in-order array
    if (preorder.size() != inorder.size() || preorder.size() <= 0)
        return NULL;

    return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
}


TreeNode *buildTree(vector<int>& pre, int lp, int rp, vector<int>& in, int li, int ri, map<int, int> &umap)
{
    if (rp - lp != ri - li || rp - lp < 0 || lp < 0 || rp >= pre.size() || li < 0 || ri >= in.size())
        return NULL;

    if (lp == rp && pre[lp] == in[li])
        return new TreeNode(pre[lp]);

    int root = umap[pre[lp]];

    TreeNode *res = new TreeNode(pre[lp]);
    res->left = buildTree(pre, lp+1, lp+root-li, in, li, root-1, umap);
    res->right = buildTree(pre, rp-ri+root+1, rp, in, root+1, ri, umap);

    return res;
}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
    // build binary tree from pre-order and in-order traversal
    // solution: recursive, find root in in-order array by hash map
    if (preorder.size() != inorder.size() || preorder.size() <= 0)
        return NULL;

    map<int, int> umap;
    for (int i = 0; i < inorder.size(); i++)
        umap[inorder[i]] = i;

    return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1, umap);
}


TreeNode* buildTreeSt(vector<int>& preorder, vector<int>& inorder)
{
    // build binary tree from pre-order and in-order traversal
    // solution: stack, visit every node in pre-order, if stack top
    // doesn't equal to current in-order, current node is left to top,
    // build node and push; if stack top equals to current in-order,
    // current in-order is outdated, pop and move until inequality,
    // current node is right to just popped stack top, build and push
    if (preorder.size() != inorder.size() || preorder.size() <= 0)
        return NULL;

    TreeNode *root = new TreeNode(preorder[0]);
    vector<TreeNode *> st;
    TreeNode *p;
    int i, j;

    st.push_back(root);
    for (i = 1, j = 0; i < preorder.size(); i++)
    {
        if (st.back()->val != inorder[j])  // left
        {
            p = new TreeNode(preorder[i]);
            st.back()->left = p;
            st.push_back(p);
        }
        else  // right
        {
            for(; !st.empty() && st.back()->val == inorder[j]; j++)
            {
                p = st.back(); st.pop_back();
            }
            p->right = new TreeNode(preorder[i]);
            st.push_back(p->right);
        }
    }

    return root;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    TreeNode *res;

    string line;
    vector<int> pre, in;
    int x;

    getline(myfile, line);
    stringstream ss(line);
    while (ss >> x)
        pre.push_back(x);

    getline(myfile, line);
    stringstream ss2(line);
    while (ss2 >> x)
        in.push_back(x);

    PrintVec(pre);
    PrintVec(in);

    res = buildTree(pre, in);
    vector<int> a = inorderTraversal(res);
    PrintVec(a);


    myfile.close();
    return 0;
}
