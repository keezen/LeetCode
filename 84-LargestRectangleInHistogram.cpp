/*
84. Largest Rectangle in Histogram
Hard

Given n non-negative integers representing the histogram's bar height where the
width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:

Input: [2,1,5,6,2,3]
Output: 10
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


int largestRectangleArea(vector<int>& heights)
{
    // largest area of rectangle
    // solution: dynamic programming

    if (heights.size() <= 0)
        return 0;

    int n = heights.size();
    vector<int> left(n, -1), right(n, n);
    int i, j;

    // find first left which is shorter than h[i]
    for (i = 1; i < n; i++)
    {
        for (j = i - 1; j >= 0 && heights[j] >= heights[i]; j = left[j]) ;
        left[i] = j;
    }

    // find first right which is shorter than h[i]
    for (i = n - 2; i >= 0; i--)
    {
        for (j = i + 1; j < n && heights[j] >= heights[i]; j = right[j]) ;
        right[i] = j;
    }

    // largest area
    int res = 0;
    for (i = 0; i < n; i++)
        res = max(res, (right[i] - left[i] - 1) * heights[i]);

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x;

        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        res = largestRectangleArea(data);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}
