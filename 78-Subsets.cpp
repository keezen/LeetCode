/*
78. Subsets
Medium

Given a set of distinct integers, nums, return all possible subsets
(the power set).

Note: The solution set must not contain duplicate subsets.

Example:
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
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


void subsets(int pos, vector<int> &nums, vector<int> &path, vector<vector<int> > &res)
{
    if (pos >= nums.size())
    {
        res.push_back(path);
        return;
    }

    path.push_back(nums[pos]);
    subsets(pos + 1, nums, path, res);
    path.pop_back();

    subsets(pos + 1, nums, path, res);
}


vector<vector<int> > subsetsBacktrack(vector<int>& nums)
{
    // find all subsets of given set
    // solution: backtrack
    vector<vector<int> > res;
    if (nums.size() <= 0)
    {
        res.push_back(nums);
        return res;
    }

    vector<int> path;
    subsets(0, nums, path, res);

    return res;
}

vector<vector<int> > subsetsBFS(vector<int>& nums)
{
    // find all subsets of given set
    // solution: iterative, BFS
    vector<vector<int> > res;
    int n = nums.size(), i, j, k;

    res.push_back(vector<int>());
    for (i = 0; i < n; i++)
        for (k = res.size(), j = 0; j < k; j++)
        {
            vector<int> t = res[j];
            t.push_back(nums[i]);
            res.push_back(t);
        }
    return res;
}


vector<vector<int> > subsets(vector<int>& nums)
{
    // find all subsets of given set
    // solution: bit, use bit to indicate whether an element in
    // subset
    vector<vector<int> > res;
    int n = nums.size(), i, j, k = 1 << n;

    for (i = 0; i < k; i++)
    {
        vector<int> path;
        for (j = 0; j < n; j ++)
            if ((i >> j) & 1)
                path.push_back(nums[j]);
        res.push_back(path);
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<vector<int> > res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        int x;
        vector<int> nums;
        while (ss >> x)
            nums.push_back(x);

        PrintVec(nums);
        cout << endl;

        res = subsets(nums);
        for (int i = 0; i < res.size(); i++)
            PrintVec(res[i]);
        cout << endl;
    }

    myfile.close();
    return 0;
}
