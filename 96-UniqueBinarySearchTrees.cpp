/*
96. Unique Binary Search Trees
Medium

Given n, how many structurally unique BST's (binary search trees)
that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
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


int numTrees(int n)
{
    // number of binary search trees given number of nodes
    // solution: dynamic programming, f(n) = \sum_{i=0}^{n-1} f(i) * f(n-1-i)

    if (n <= 0)
        return 0;

    vector<int> dp(n + 1, 0);
    int i, j;

    dp[0] = dp[1] = 1;
    for (i = 2; i <= n; i++)
        for (j = 0; j <= i - 1; j++)
            dp[i] += dp[j] * dp[i-1-j];

    return dp[n];
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");


    int res;

    string line;
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int n;
        ss >> n;
        cout << n << endl;

        res = numTrees(n);
        cout << res << endl;
    }


    myfile.close();
    return 0;
}
