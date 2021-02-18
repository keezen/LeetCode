/*
128. Longest Consecutive Sequence
Hard

Given an unsorted array of integers, find the length of the longest
consecutive elements sequence.

Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
Therefore its length is 4.
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


int longestConsecutiveLink(vector<int>& nums)
{
    // length of longest consecutive sequence in unsorted array
    // solution: construct mapping for num to position, link every num to previous,
    //     then compute length of each linked list

    if (nums.size() <= 0)
        return 0;

    // dict of node to position
    int i, j;
    unordered_map<int, int> umap;
    for (i = 0; i < nums.size(); i++)
        umap.insert(make_pair(nums[i], i));
    
    // link every node to previous
    vector<int> prevs(nums.size(), 0);
    for (i = 0; i < nums.size(); i++)
        if (umap.find(nums[i]-1) == umap.end())
            prevs[i] = i;
        else
            prevs[i] = umap[nums[i]-1];

    // length of longest consecutive sequence
    vector<bool> visited(nums.size(), false);
    int max_len = 1, len = 1;
    for (i = 0; i < nums.size(); i++)
    {
        if (visited[i])
            continue;

        for (j = i, len = 1; prevs[j] != j; j = prevs[j])
        {
            visited[j] = true;
            len++;
        }
        max_len = max(len, max_len);
    }
    
    return max_len;
}


int longestConsecutive(vector<int>& nums)
{
    // length of longest consecutive sequence in unsorted array
    // solution: hash set, extend from every initial, compute length

    if (nums.size() <= 0)
        return 0;

    // hash set
    int i;
    unordered_set<int> uset;
    for (i = 0; i < nums.size(); i++)
        uset.insert(nums[i]);

    // extend from each initial
    int max_len = 1, len = 1, num;
    for (auto it = uset.begin(); it != uset.end(); it++)
    {
        num = *it;
        len = 1;

        // not initial
        if (uset.find(num - 1) != uset.end())
            continue;
        
        // length from initial
        while (uset.find(num + 1) != uset.end())
        {
            num++;
            len++;
        }
        max_len = max(max_len, len);
    }
    
    return max_len;
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

        res = longestConsecutive(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}