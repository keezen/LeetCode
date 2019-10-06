/*
41. First Missing Positive
Hard

Given an unsorted integer array, find the smallest missing positive
integer.

Example 1:
Input: [1,2,0]
Output: 3

Example 2:
Input: [3,4,-1,1]
Output: 2

Example 3:
Input: [7,8,9,11,12]
Output: 1

Note:
Your algorithm should run in O(n) time and uses constant extra space.
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


int firstMissingPositive(vector<int>& nums)
{
    // find smallest missing positive integer
    // solution: in-place sorting, place all positives no larger
    // than n in its right place

    if (nums.size() <= 0)
        return 1;

    int n = nums.size(), i = 0;

    // put every positive no larger than n in its right place
    while (i < n)
    {
        if (0 < nums[i] && nums[i] <= n && nums[i] != nums[nums[i] - 1])
            swap(nums[i], nums[nums[i] - 1]);
        else
            i++;
    }

    for (i = 0; i < n; i++)
        if (nums[i] != i + 1)
            return i + 1;

    return n + 1;
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

        PrintVec(nums);

        res = firstMissingPositive(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}