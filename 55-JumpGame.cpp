/*
55. Jump Game
Medium

Given an array of non-negative integers, you are initially
positioned at the first index of the array.

Each element in the array represents your maximum jump
length at that position.

Determine if you are able to reach the last index.

Example 1:
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to
the last index.

Example 2:
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what.
             Its maximum jump length is 0, which makes it
             impossible to reach the last index.
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


bool canJump(vector<int>& nums)
{
    // whether one can jump to the end
    // solution: keep track of farthest boundary that can be reached

    if (nums.size() <= 0)
        return false;

    int n = nums.size(), i;
    int b = 0;  // 

    for (i = 0; i < n; i++)
    {
        if (i > b)
            return false;
        else if (b >= n - 1)
            return true;
        else
            b = max(b, i + nums[i]);
    }

    return false;    
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    bool res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        int x;
        vector<int> nums;
        while (ss >> x)
            nums.push_back(x);

        PrintVec(nums);

        res = canJump(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}