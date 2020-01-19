/*
56. Merge Intervals
Medium

Given a collection of intervals, merge all overlapping intervals.

Example 1:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them
    into [1,6].

Example 2:
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

NOTE: input types have been changed on April 15, 2019. Please reset
    to default code definition to get new method signature.
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


bool compare_interval(vector<int> &a, vector<int> &b)
{
    if (a[0] < b[0])
        return true;

    if (a[0] > b[0])
        return false;

    if (a[1] < b[1])
        return true;

    if (a[1] > b[1])
        return false;
    
    return false;
}


vector<vector<int> > merge(vector<vector<int> >& intervals)
{
    // merge overlapping intervals
    // solution: sort, and merge every interval with stack top
    // if they overlap

    if (intervals.size() <= 0 || intervals[0].size() <= 0)
        return intervals;

    int n = intervals.size(), i;

    // sort
    sort(intervals.begin(), intervals.end(), compare_interval);

    // merge
    vector<vector<int> > res;
    res.push_back(intervals[0]);

    for (i = 1; i < n; i++)
    {
        // overlap, merge
        if (intervals[i][0] <= res.back()[1])
            res.back()[1] = max(intervals[i][1], res.back()[1]);
        else
            res.push_back(intervals[i]);
    }

    return res;
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

    for (auto x: matrix)
        PrintVec(x);
    cout << endl;

    res = merge(matrix);
    for (auto x: res)
        PrintVec(x);

    myfile.close();
    return 0;
}