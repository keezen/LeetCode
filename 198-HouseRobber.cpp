/*
198. House Robber
Medium

You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, the only constraint
stopping you from robbing each of them is that adjacent houses have
security systems connected and it will automatically contact the police 
if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, 
return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 400
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <unordered_set>
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


int rob(vector<int>& nums)
{
    // maximum sum of element without adjacent
    // solution: dp, dp[i] indicates the maximum sum ending with i

    if (nums.size() <= 0)
        return 0;

    int i, j, n = nums.size(), m = 0;
    int p1, p2 = 0, p3 = 0, dp;
    m = p1 = nums[0];
    for (i = 1; i < n; i++)
    {
        dp = 0;
        if (i >= 2)
            dp = max(dp, p2);
        if (i >= 3)
            dp = max(dp, p3);

        dp += nums[i];
        m = max(dp, m);

        p3 = p2;
        p2 = p1;
        p1 = dp;
    }

    return m;
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

        res = rob(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}