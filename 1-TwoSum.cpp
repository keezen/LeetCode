/*
1. Two Sum
Easy

Given an array of integers, return indices of the two numbers such
that they add up to a specific target.

You may assume that each input would have exactly one solution,
and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_map>
using namespace std;


ifstream myfile("a.txt");


template <typename T> ostream & operator<<(ostream &os, pair<T, T> &rhs)
{
    cout << rhs.first << ',' << rhs.second;
    return os;
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


vector<int> twoSum(vector<int>& nums, int target)
{
    // find two elements whose sum is target

    if (nums.size() <= 0)
        return vector<int>();

    vector<int> res(2, 0);
    unordered_map<int, int> imap;
    unordered_map<int, int>::iterator it;
    int i;

    for (i = 0; i < nums.size(); i++)
    {
        it = imap.find(target - nums[i]);
        if (it != imap.end())
        {
            res[0] = imap[target - nums[i]];
            res[1] = i;
            return res;
        }
        else
            imap[nums[i]] = i;
    }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    vector<int> res;

    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x, target;
        
        while (ss >> x)
        {
            data.push_back(x);
        }

        getline(myfile, line);
        stringstream ss2(line);
        ss2 >> target;

        PrintVec(data);
        cout << target << endl;

        res = twoSum(data, target);
        PrintVec(res);
    }

    return 0;
}