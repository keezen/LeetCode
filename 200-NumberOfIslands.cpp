/*
200. Number of Islands
Medium

Given an m x n 2D binary grid grid which represents a map of '1's (land)
and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent
lands horizontally or vertically. You may assume all four edges of the
grid are all surrounded by water.

 
Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
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


int numIslands(vector<vector<char>>& grid)
{
    // number of connected node groups
    // solution: DFS, stack

    if (grid.size() <= 0 || grid[0].size() <= 0)
        return 0;

    int dxs[4] = {-1, 1, 0, 0};
    int dys[4] = {0, 0, -1, 1};
    vector<int> st;
    int m = grid.size(), n = grid[0].size(), i, j, k, x, y, u, v, t;
    vector<bool> visited(m * n, false);
    int cnt = 0;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (grid[i][j] == '1' && !visited[i*n+j])
            {
                visited[i*n+j]=true;
                st.push_back(i*n+j);
                while (!st.empty())
                {
                    t = st.back();
                    // cout << t << endl;
                    x = t / n, y = t % n;
                    st.pop_back();
                    for (k = 0; k < 4; k++)
                    {
                        u = x+dxs[k], v = y+dys[k];
                        if ((0 <= u && u < m) && (0 <= v && v < n) && grid[u][v] == '1' && !visited[u*n+v])
                        {
                            visited[u*n+v] = true;
                            st.push_back(u*n+v);
                        }
                    }
                }
                cnt++;
                // cout << endl;
            }

    return cnt;
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

    res = numIslands(grid);
    cout << res << endl;

    myfile.close();
    return 0;
}