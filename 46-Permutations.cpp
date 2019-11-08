/*
46. Permutations
Medium

Given a collection of distinct integers, return all possible
permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
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


void permute(vector<int>& nums, int pos, vector<vector<int> > &res)
{
    // permute arrays from postion 'pos'

    if (nums.size() <= 0)
        return;
    
    if (pos >= nums.size() - 1)
    {
        res.push_back(nums);
        return;
    }

    int i;
    for (i = pos; i < nums.size(); i++)
    {
        swap(nums[pos], nums[i]);
        permute(nums, pos + 1, res);
        swap(nums[pos], nums[i]);
    }
}


vector<vector<int> > permute(vector<int>& nums)
{
    // find all permutations of array
    // solution: backtrack

    vector<vector<int> > res;
    if (nums.size() <= 0)
        return res;
    
    permute(nums, 0, res);
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

        res = permute(nums);
        for (auto x: res)
            PrintVec(x);
    }

    myfile.close();
    return 0;
}