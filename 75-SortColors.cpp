/*
75. Sort Colors
Medium

Given an array with n objects colored red, white or blue, sort them
in-place so that objects of the same color are adjacent, with the
colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red,
white, and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Follow up:

A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite
array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i].first << ' ' << data[i].second << ' ';
    cout << data.back().first << ' ' << data.back().second << endl;
}


void sortColorsCount(vector<int>& nums)
{
    // sort colors array
    // solution: count sort, two pass

    if (nums.size() <= 0)
        return;

    vector<int> cnt(3, 0);
    int i, j;

    for (i = 0; i < nums.size(); i++)
        cnt[nums[i]] += 1;

    i = 0;
    for (j = 0; j < cnt.size(); j++)
    {
        while (cnt[j] > 0)
        {
            nums[i++] = j;
            cnt[j]--;
        }
    }
}


void sortColors(vector<int>& nums)
{
    // sort colors array
    // solution: dutch partion, one pass

    if (nums.size() <= 0)
        return;

    int i, j, k, n = nums.size();
    i = 0; j = n - 1; k = 0;  // three pointers
    while (k <= j)
    {
        if (nums[k] == 0)
            swap(nums[i++], nums[k++]);
        else if (nums[k] == 1)
            k++;
        else
            swap(nums[j--], nums[k]);
    }
}


int main(int argc, char *argv[])
{
    string word1("intention");
    string word2("execution");
    int res;

    cout << word1 << endl;
    cout << word2 << endl;

    res = minDistance(word1, word2);
    cout << res << endl;

    return 0;
}