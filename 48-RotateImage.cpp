/*
48. Rotate Image
Medium

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to
modify the input 2D matrix directly. DO NOT allocate another
2D matrix and do the rotation.

Example 1:

Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]

Example 2:

Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
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


void rotateInsert(vector<vector<int> >& matrix)
{
    // rotate matrix 90 degrees clockwise
    // solution: insert clockwise, (i,j) -> (j,n-1-i)

    if (matrix.size() <= 0 or matrix[0].size() <= 0)
        return;

    if (matrix.size() != matrix[0].size())
        return;

    int n = matrix.size();
    int i, j, k;
    int x, y, z, t, e;
    for (i = 0; i < n / 2; i++)
        for (j = i; j < n - 1 - i; j++)
        {
            x = i; y = j; e = matrix[i][j];
            for (k = 0; k < 4; k++)
            {
                z = x; x = y; y = n - 1 - z;
                t = matrix[x][y];
                matrix[x][y] = e;
                e = t;
            }
        }   
}


void rotate(vector<vector<int> >& matrix)
{
    // rotate matrix 90 degrees clockwise
    // solution: first reverse up to down, then swap the symmetry

    if (matrix.size() <= 0 or matrix[0].size() <= 0)
        return;

    if (matrix.size() != matrix[0].size())
        return;

    int n = matrix.size();
    int i, j;

    reverse(matrix.begin(), matrix.end());
    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            swap(matrix[i][j], matrix[j][i]);
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<vector<int> > res;

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

    for (auto &x: matrix)
        PrintVec(x);

    rotate(matrix);
    for (auto &x: matrix)
        PrintVec(x);

    myfile.close();
    return 0;
}