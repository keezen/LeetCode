/*
221. Maximal Square
Medium

Given an m x n binary matrix filled with 0's and 1's,
find the largest square containing only 1's and return its area.


Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4

Example 2:
Input: matrix = [["0","1"],["1","0"]]
Output: 1

Example 3:
Input: matrix = [["0"]]
Output: 0
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <unordered_set>
using namespace std;


template <typename T> ostream & operator<<(ostream &os, pair<T,T> &x)
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


int maximalSquareLower(vector<vector<char>>& matrix)
{
    // maximal square in graph
    // solution: record first lower element in left and right

    if (matrix.size() <= 0 || matrix[0].size() <= 0)
        return 0;

    int m = matrix.size(), n = matrix[0].size(), i, j, k;
    int w, h, zero_left, zero_right;
    vector<int> height(n, 0);
    vector<int> lower_left(n, -1), lower_right(n, n);
    int maximal = 0;
    for (i = 0; i < m; i++)
    {
        // compute height
        for (j = 0; j < n; j++)
            height[j] = matrix[i][j] == '1' ? height[j]+1 : 0;
        
        // first lower element in left and right
        // lower_left[0] = -1;
        // for (j = 1; j < n; j++)
        // {
        //     for (k = j-1; k >= 0 && height[k] >= height[j]; k = lower_left[k]) ;
        //     lower_left[j] = k;

        // }
        // lower_right[n-1] = n;
        // for (j = n - 2; j >= 0; j--)
        // {
        //     for (k = j+1; k < n && height[k] >= height[j]; k = lower_right[k]) ;
        //     lower_right[j] = k;
        // }
        zero_left = -1;  // first 0 in left
        for (j = 0; j < n; j++)
        {
            if (height[j] > 0)
                lower_left[j] = max(lower_left[j], zero_left);
            else
                lower_left[j] = -1;

            if (height[j] == 0)
                zero_left = j;
        }
        zero_right = n;  // first 0 in right
        for (j = n-1; j >= 0; j--)
        {
            if (height[j] > 0)
                lower_right[j] = min(lower_right[j], zero_right);
            else
                lower_right[j] = n;

            if (height[j] == 0)
                zero_right = j;
        }

        // maximal square
        for (j = 0; j < n; j++)
        {
            w = lower_right[j] - lower_left[j] - 1;
            h = height[j];
            w = w < h ? w : h;
            if (w * w > maximal)
                maximal = w * w;
        }
    }

    return maximal;
}


int maximalSquare(vector<vector<char>>& matrix)
{
    // maximal square in graph
    // solution: dp, dp(i,j) means maximal width of square whose bottom
    //     right corner is m(i,j), 
    //     dp(i,j) = min(dp(i-1,j), dp(i,j-1), dp(i-1,j-1)) + 1

    if (matrix.size() <= 0 || matrix[0].size() <= 0)
        return 0;

    int m = matrix.size(), n = matrix[0].size(), i, j, t;
    vector<int> dp(n, 0);
    int maximal = 0, prev;
    for (i = 0; i < m; i++)
    {
        prev = dp[0];  // dp(i-1,j-1)
        dp[0] = matrix[i][0] == '1' ? 1 : 0;
        maximal = max(dp[0] * dp[0], maximal);
        for (j = 1; j < n; j++)
        {
            t = dp[j];
            if (matrix[i][j] == '0')
                dp[j] = 0;
            else
            {
                dp[j] = min(min(dp[j-1], dp[j]), prev) + 1;
                maximal = max(dp[j], maximal);
            }
            prev = t;
        }
    }

    return maximal * maximal;
}



int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string line;
    vector<vector<char>> grid;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        char x;
        vector<char> nums;
        while (ss >> x)
            nums.push_back(x);

        PrintVec(nums);
        grid.push_back(nums);
    }

    res = maximalSquare(grid);
    cout << res << endl;

    myfile.close();
    return 0;
}