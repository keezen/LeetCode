/*
62. Unique Paths
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start'
in the diagram below).

The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid
(marked 'Finish' in the diagram below).

How many possible unique paths are there?

Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:
Input: m = 7, n = 3
Output: 28
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


int uniquePaths(int m, int n)
{
    // number of unique paths from top-left to bottom-right
    // solution: dynamic programming

    if (m < 0 || m > 100 || n < 0 || n > 100)
        return 0;

    vector<int> dp(n, 0);
    int i, j;

    for (j = 0; j < n; j++)
        dp[j] = 1;

    for (i = 1; i < m; i++)
        for (j = 1; j < n; j++)
        {
            dp[j] = dp[j-1] + dp[j];
        }
        
    return dp[n-1];
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        int m, n;
        ss >> m >> n;

        cout << m << ' ' << n << endl;

        res = uniquePaths(m, n);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}
