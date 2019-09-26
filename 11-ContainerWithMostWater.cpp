/*
11. Container With Most Water
Medium

Given n non-negative integers a1, a2, ..., an , where each represents
a point at coordinate (i, ai). n vertical lines are drawn such that
the two endpoints of line i is at (i, ai) and (i, 0). Find two lines,
which together with x-axis forms a container, such that the container
contains the most water.

Note: You may not slant the container and n is at least 2.

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7].
In this case, the max area of water (blue section) the container can
contain is 49.

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
using namespace std;


template <typename T> ostream & operator<<(ostream &os, pair<T, T> &rhs)
{
    cout << rhs.first << ',' << rhs.second;
    return os;
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


int maxAreaBF(vector<int>& height)
{
    // max area of two heights
    // solution: brute force, check every pair

    int n = height.size();
    int i, j;

    int res = 0, area;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
        {
            area = (j - i) * min(height[i], height[j]);
            res = max(area, res);
        }
    
    return res;
}


int maxArea(vector<int>& height)
{
    // max area of two heights
    // solution: brute force, check every pair

    int i = 0, j = height.size() - 1;
    int res = 0, area;

    while (i < j)
    {
        area = min(height[i], height[j]) * (j - i);
        res = max(area, res);

        if (height[i] < height[j])
            i++;
        else
            j--;     
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string line;
    int res;

    while(getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        vector<int> data;
        int x;
        stringstream ss(line);
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        res = maxArea(data);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}