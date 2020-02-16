/*
85. Maximal Rectangle
Hard

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
containing only 1's and return its area.

Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


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


int maximalRectangle(vector<vector<char> >& matrix)
{
    // maximum rectangle containing only 1s
    // solution: dynamic programming, max area is max of
    // h(i,j) * (r(i,j) - l(i,j) - 1)

    if (matrix.size() <= 0 || matrix[0].size() <= 0)
        return 0;

    int m = matrix.size(), n = matrix[0].size();
    vector<int> height(n, 0), left(n, -1), right(n, n);
    int i, j, l, r;
    int res = 0;

    for (i = 0; i < m; i++)
    {
        // height
        for (j = 0; j < n; j++)
            if (matrix[i][j] == '1')
                height[j] += 1;
            else
                height[j] = 0;

        // left
        for (l = -1, j = 0; j < n; j++)
            if (matrix[i][j] == '1')
                left[j] = max(left[j], l);
            else
            {
                left[j] = -1; l = j;
            }

        // right
        for (r = n, j = n - 1; j >= 0; j--)
            if (matrix[i][j] == '1')
                right[j] = min(right[j], r);
            else
            {
                right[j] = n; r = j;
            }

        // area
        for (j = 0; j < n; j++)
            res = max(res, (right[j]-left[j]-1) * height[j]);
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    vector<vector<char> > data;
    string line;
    while(getline(myfile, line))
    {
        // stringstream ss(line);
        vector<char> row;

        for (int i = 0; i < line.size(); i++)
            row.push_back(line[i]);
        data.push_back(row);

        // while (ss >> x)
        //     data.push_back(x);
    }

    for (int i = 0; i < data.size(); i++)
        PrintVec(data[i]);

    res = maximalRectangle(data);
    cout << res << endl;

    myfile.close();
    return 0;
}
