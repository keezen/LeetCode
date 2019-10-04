/*
39. Combination Sum
Medium

Given a set of candidate numbers (candidates) (without duplicates)
and a target number (target), find all unique combinations in
candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited
number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]

Example 2:
Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
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


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    // print out a vector
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
        cout << ((i == data.size() - 1) ? eol : sep);
    }
}


void combinationSum(vector<int>& nums, int pos, int target, vector<int> &path, vector<vector<int> > &res)
{
    if (target == 0)
    {
        res.push_back(path);
        return;
    }

    if (pos >= nums.size())
        return;

    for (int i = pos; i < nums.size(); i++)
        if (nums[i] <= target)
        {
            path.push_back(nums[i]);
            combinationSum(nums, i, target - nums[i], path, res);
            path.pop_back();
        }
}


vector<vector<int> > combinationSum(vector<int>& candidates, int target)
{
    // find all combinations whose sum is target
    // solution: backtrack

    vector<vector<int> > res;
    if (candidates.size() <= 0)
        return res;

    vector<int> path;
    sort(candidates.begin(), candidates.end());
    combinationSum(candidates, 0, target, path, res);

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

        getline(myfile, line);
        stringstream ss2(line);
        int target;
        ss2 >> target;

        PrintVec(nums);
        cout << target << endl;

        res = combinationSum(nums, target);
        for (auto u: res)
            PrintVec(u);
    }

    myfile.close();
    return 0;
}