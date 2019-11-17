/*
49. Group Anagrams
Medium

Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note:

All inputs will be in lowercase.
The order of your output does not matter.
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


vector<vector<string> > groupAnagrams(vector<string>& strs)
{
    // group anagrams together

    vector<vector<string> > res;
    if (strs.size() <= 1)
    {
        res.push_back(strs);
        return res;
    }

    int n = strs.size(), i, j;
    unordered_map<string, int> umap;
    for (i = 0; i < n; i++)
    {
        string a = strs[i];
        sort(a.begin(), a.end());
        if (umap.find(a) == umap.end())
        {
            res.push_back(vector<string>(1, strs[i]));
            umap[a] = res.size() - 1;
        }
        else
        {
            res[umap[a]].push_back(strs[i]);
        }      
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<vector<string> > res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        string x;
        vector<string> strs;
        while (ss >> x)
            strs.push_back(x);

        PrintVec(strs);

        res = groupAnagrams(strs);
        for (auto &x: res)
            PrintVec(x);
    }

    myfile.close();
    return 0;
}