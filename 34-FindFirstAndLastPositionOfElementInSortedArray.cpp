/*
34. Find First and Last Position of Element in Sorted Array
Medium

Given an array of integers nums sorted in ascending order,
find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
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


vector<int> searchRange(vector<int>& nums, int target)
{
    // find first and last position of element in sorted array
    // solution: binary search

    vector<int> res(2, -1);
    if (nums.size() <= 0)
        return res;

    int l, r, m;
    int n = nums.size();
    l = 0; r = n - 1;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] == target && (m == 0 || nums[m-1] < target))
            break;
        else if (nums[m] > target || (nums[m] == target && m > 0 && nums[m-1] == target))
            r = m - 1;
        else
            l = m + 1;     
    }
    if (l <= r) res[0] = m;

    l = 0; r = n - 1;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] == target && (m == n-1 || nums[m+1] > target))
            break;
        else if (nums[m] < target || (nums[m] == target && m < n-1 && nums[m+1] == target))
            l = m + 1;
        else
            r = m - 1;     
    }
    if (l <= r) res[1] = m;

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<int> res;

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

        res = searchRange(nums, target);
        PrintVec(res);
    }

    myfile.close();
    return 0;
}