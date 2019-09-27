/*
15. 3Sum
Medium

Given an array nums of n integers, are there elements
a, b, c in nums such that a + b + c = 0? Find all
unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
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


vector<vector<int> > threeSum(vector<int>& nums)
{
    // find all unique triplets whose sum is 0
    // solution: sort array, fix first element
    // use two-pointer method to find the other two elements

    vector<vector<int> > res;
    if (nums.size() <= 0)
        return res;

    sort(nums.begin(), nums.end());

    int n = nums.size();
    int i = 0, j, k, t;
    vector<int> triplet(3, 0);
    for (i = 0; i < n; i++)
    {
        // skip repeated first element
        if (i > 0 && nums[i] == nums[i-1])
            continue;
        
        // two pointer
        j = i + 1; k = n - 1; t = -nums[i];
        while (j < k)
        {
            if (nums[j] + nums[k] < t || (j > i + 1 && nums[j] == nums[j-1]))
                j++;
            else if (nums[j] + nums[k] > t || (k < n - 1 && nums[k] == nums[k+1]))
                k--;
            else if (nums[j] + nums[k] == t)
            {
                triplet[0] = nums[i];
                triplet[1] = nums[j];
                triplet[2] = nums[k];
                res.push_back(triplet);
                j++;
            }
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string line;
    vector<vector<int> > res;

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

        res = threeSum(data);
        for (auto &u: res)
            PrintVec(u);
    }

    myfile.close();
    return 0;
}