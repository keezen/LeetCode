/*
31. Next Permutation
Medium

Implement next permutation, which rearranges numbers into
the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it
as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra
memory.

Here are some examples. Inputs are in the left-hand column
and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
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


void nextPermutation(vector<int>& nums)
{
    // next permutation of current array

    if (nums.size() <= 1)
        return;

    // find first reversed unordered element
    int i;
    for (i = nums.size() - 2; i >= 0 && nums[i] >= nums[i + 1]; i--) ;

    if (i < 0)
    {
        reverse(nums.begin(), nums.end());
        return;
    }

    // swap it with the minimum value larger than it
    int j;
    for (j = i + 1; j < nums.size() && nums[j] > nums[i]; j++) ;
    swap(nums[i], nums[--j]);

    // reverse the right part
    reverse(nums.begin() + i + 1, nums.end());
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

        nextPermutation(nums);
        PrintVec(nums);
    }

    myfile.close();
    return 0;
}