/*
169. Majority Element
Easy


Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. 
You may assume that the majority element always exists in the array.


Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-231 <= nums[i] <= 231 - 1
 

Follow-up: Could you solve the problem in linear time and in O(1) space?
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


int majorityElement(vector<int>& nums)
{
    // find element appears n/2 times above
    // solution: count same element, vanish two different elements,
    //     majoriry element will remain last

    if (nums.size() <= 0)
        return -1;

    int i, cnt = 0, major = 0;
    for (i = 0; i < nums.size(); i++)
    {
        if (cnt == 0)
        {
            major = nums[i];
            cnt++;
        }
        else if (major != nums[i])
            cnt--;
        else
            cnt++;
    }

    return major;
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

        res = majorityElement(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}