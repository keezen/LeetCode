/*
64. Minimum Path Sum
Medium

Given a m x n grid filled with non-negative numbers, find a path
from top left to bottom right which minimizes the sum of all
numbers along its path.

Note: You can only move either down or right at any point in time.

Example:
Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
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


int minPathSum(vector<vector<int>>& grid)
{
    // minimum path sum from top-left to bottom-right
    // solution: dynamic programming

    if (grid.size() <= 0 || grid[0].size() <= 0)
        return 0;

    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n, 0);
    int i, j;

    dp[0] = grid[0][0];
    for (j = 1; j < n; j++)
        dp[j] = dp[j-1] + grid[0][j];

    for (i = 1; i < m; i++)
    {
        dp[0] += grid[i][0];
        for (j = 1; j < n; j++)
            dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
    }

    return dp[n-1];
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string line;
    vector<vector<int> > matrix;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        int x;
        vector<int> nums;
        while (ss >> x)
            nums.push_back(x);

        matrix.push_back(nums);
    }

    for (auto x: matrix)
        PrintVec(x);

    res = minPathSum(matrix);
    cout << res << endl;

    myfile.close();
    return 0;
}