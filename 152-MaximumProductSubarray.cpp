/*
152. Maximum Product Subarray
Medium

Given an integer array nums, find a contiguous non-empty subarray within
the array that has the largest product, and return the product.

It is guaranteed that the answer will fit in a 32-bit integer.

A subarray is a contiguous subsequence of the array.

 
Example 1:
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 

Constraints:
1 <= nums.length <= 2 * 104
-10 <= nums[i] <= 10
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <unordered_set>
# include <climits>
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


int maxProductPN(vector<int>& nums)
{
    // largest product of sub-array
    // solution: track positive and negative with maximum absolute
    //     value ending with current element

    if (nums.size() <= 0)
        return 0;

    if (nums.size() == 1)
        return nums[0];
    
    int max_pro = 0;
    int maxp = 0, maxn = 0;
    int i, t;
    for (i = 0; i < nums.size(); i++)
    {
        if (nums[i] > 0)
        {
            maxp = maxp > 0 ? maxp*nums[i] : nums[i];
            maxn = maxn < 0 ? maxn*nums[i] : 0;
        }
        else if (nums[i] < 0)
        {
            t = maxp;
            maxp = maxn < 0 ? maxn*nums[i] : 0;
            maxn = t > 0 ? t*nums[i] : nums[i];
        }
        else
        {
            maxp = 0;
            maxn = 0;
        }

        max_pro = max(max_pro, maxp);
    }

    return max_pro;
}


int maxProductMaxMin(vector<int>& nums)
{
    // largest product of sub-array
    // solution: track maximum and minimum product ending with current element

    if (nums.size() <= 0)
        return 0;

    if (nums.size() == 1)
        return nums[0];
    
    int max_pro = nums[0];
    int maxp = nums[0], minp = nums[0];
    int i;
    for (i = 1; i < nums.size(); i++)
    {
        if (nums[i] < 0)
            swap(maxp, minp);

        maxp = max(maxp * nums[i], nums[i]);
        minp = min(minp * nums[i], nums[i]);

        max_pro = max(max_pro, maxp);
    }

    return max_pro;
}


int maxProduct(vector<int>& nums)
{
    // largest product of sub-array
    // solution: two pass, target sub-array must start from either end
    //     except for 0

    if (nums.size() <= 0)
        return 0;

    if (nums.size() == 1)
        return nums[0];
    
    int max_pro = INT32_MIN, pro;
    int i;
    for (i = 0, pro = 1; i < nums.size(); i++)
    {
        pro *= nums[i];
        max_pro = max(pro, max_pro);
        if (nums[i] == 0)
            pro = 1;
    }

    for (i = nums.size()-1, pro = 1; i >= 0; i--)
    {
        pro *= nums[i];
        max_pro = max(pro, max_pro);
        if (nums[i] == 0)
            pro = 1;
    }

    return max_pro;
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

        res = maxProduct(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}