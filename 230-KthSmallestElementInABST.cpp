/*
230. Kth Smallest Element in a BST
Medium


Given the root of a binary search tree, and an integer k, return the kth
(1-indexed) smallest element in the tree.

 
Example 1:
Input: root = [3,1,4,null,2], k = 1
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
 

Constraints:
The number of nodes in the tree is n.
1 <= k <= n <= 104
0 <= Node.val <= 104
 

Follow up: If the BST is modified often (i.e., we can do insert and delete operations)
and you need to find the kth smallest frequently, how would you optimize?
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


int kthSmallest(TreeNode* root, int k)
{
    // k-th smallest element in BST
    // solution: in-order traversal

    if (root == NULL || k < 1)
        return -1;

    vector<TreeNode *> st;
    TreeNode *p = root;
    int cnt = 0;
    st.push_back(root);
    while (p != NULL || !st.empty())
    {
        if (p != NULL)  // go left
        {
            st.push_back(p);
            p = p->left;
        }
        else  // left finished, visit top
        {
            p = st.back();
            st.pop_back();
            cnt++;
            if (cnt == k)
                return p->val;
            p = p->right;
        }
    }

    return 0;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    int k = 3;
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    res = kthSmallest(root, k);
    cout << res << endl;
    // PrintVec(res);


    myfile.close();
    return 0;
}
