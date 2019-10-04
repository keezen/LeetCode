/*
33. Search in Rotated Sorted Array
Medium

Suppose an array sorted in ascending order is rotated at
some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the
array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order
of O(log n).

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
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


int search(vector<int> &nums, int target)
{
    // search in rotated sorted array
    // solution: binary search

    if (nums.size() <= 0)
        return -1;

    int l, r, m;

    l = 0; r = nums.size() - 1;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] == target)
            return m;
        else if (nums[l] <= nums[m])
        {
            if (nums[l] <= target && target < nums[m])
                r = m - 1;
            else
                l = m + 1;
        }
        else if (nums[m] <= nums[r])
        {
            if (nums[m] < target && target <= nums[r])
                l = m + 1;
            else
                r = m - 1;
        }
    }

    return -1;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

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

        res = search(nums, target);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}