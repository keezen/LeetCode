/*
139. Word Break
Medium

Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, determine if s can be segmented into a space-separated
sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <unordered_set>
using namespace std;


ifstream myfile("a.txt");


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


bool wordBreak(string s, vector<string>& wordDict)
{
    // whether string can be segmented into words
    // solution: dynamic programming, using HashSet, O(N^3)

    if (s.size() <= 0)
        return false;

    unordered_set<string> uset(wordDict.begin(), wordDict.end());
    int n = s.size(), i, j;
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (dp[j] && uset.find(s.substr(j, i-j)) != uset.end())
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}


bool wordBreakIter(string s, vector<string>& wordDict)
{
    // whether string can be segmented into words
    // solution: dynamic programming, O(N^2 * M)

    if (s.size() <= 0)
        return false;

    int n = s.size(), m = wordDict.size(), k, i, j;
    string t;
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j < m; j++)
        {
            t = wordDict[j];
            k = t.size();
            if (i >= k && dp[i-k] && s.substr(i-k, k) == t)
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}


int main(int argc, char *argv[])
{
    string s = "leetcode";
    vector<string> wordDict(2);
    bool res;

    wordDict[0] = "leet";
    wordDict[1] = "code";

    cout << s << endl;
    PrintVec(wordDict);

    res = wordBreak(s, wordDict);
    cout << (res ? "true" : "false") << endl;

    return 0;
}