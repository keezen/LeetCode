/*
53. Maximum Subarray
Easy

Given an integer array nums, find the contiguous subarray 
(containing at least one number) which has the largest
sum and return its sum.

Example:
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:
If you have figured out the O(n) solution, try coding another
solution using the divide and conquer approach, which is more
subtle.
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


int maxSubArrayDP(vector<int>& nums)
{
    // max sum of contiguous sub-array
    // solution: use dp to compute max sum of sub-array ending
    // with every position

    if (nums.size() <= 0)
        return 0;

    int res = 0, max_sum;
    int i;

    res = max_sum = nums[0];
    for (i = 1; i < nums.size(); i++)
    {
        if (max_sum <= 0)
            max_sum = nums[i];
        else
            max_sum += nums[i];
        
        res = max(max_sum, res);
    }

    return res;
}


struct Node {
    int lmax;  // max subarray sum starting from left
    int rmax;  // max subarray sum ending with right
    int max_sum;  // max sum of subarray
    int sum;  // sum of whole array
    Node(int l = 0, int r = 0, int m = 0, int s = 0)
        : lmax(l), rmax(r), max_sum(m), sum(s)
    {}
};


Node maxSubArray(vector<int>& nums, int l, int r)
{
    // max sum of contiguous sub-array
    // solution: divide and conquer

    if (l == r)
        return Node(nums[l], nums[l], nums[l], nums[l]);
    
    Node n, n1, n2;
    int mid = (l + r) / 2;
    n1 = maxSubArray(nums, l, mid);
    n2 = maxSubArray(nums, mid + 1, r);
    n.lmax = max(n1.lmax, n1.sum + n2.lmax);
    n.rmax = max(n2.rmax, n2.sum + n1.rmax);
    n.max_sum = max(max(n1.max_sum, n2.max_sum), n1.rmax + n2.lmax);
    n.sum = n1.sum + n2.sum;

    return n;
}


int maxSubArray(vector<int>& nums)
{
    // max sum of contiguous sub-array
    // solution: divide and conquer

    if (nums.size() <= 0)
        return 0;

    Node n = maxSubArray(nums, 0, nums.size() - 1);
    return n.max_sum;
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

        res = maxSubArray(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}