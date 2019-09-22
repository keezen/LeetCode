/*
3. Longest Substring Without Repeating Characters
Medium

Given a string, find the length of the longest substring without
repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 

Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring,
             "pwke" is a subsequence and not a substring.
*/

# include <iostream>
# include <vector>
# include <unordered_map>
using namespace std;


int lengthOfLongestSubstringBack(string s)
{
    // longest unrepeated substring
    // solution: calculate longest unrepeated substring
    // ending with every position

    if (s.size() <= 0)
        return 0;

    int n = s.size(), m;
    vector<int> sub(n, 0);
    int i, j;

    int res = 1;
    sub[0] = 1;
    for (i = 1; i < s.size(); i++)
    {
        m = sub[i - 1];
        for (j = i - 1; j >= i - m && s[j] != s[i]; j--) ;
        sub[i] = i - j;
        if (sub[i] > res) res = sub[i];
    }

    return res;
}


int lengthOfLongestSubstringLess(string s)
{
    // longest unrepeated substring
    // solution: calculate longest unrepeated substring
    // ending with every position, less memory
    if (s.size() <= 0)
        return 0;

    int n = s.size(), m;
    int i, j;

    int res = 1;
    int sub = 1;  // length of substring in last position
    for (i = 1; i < s.size(); i++)
    {
        m = sub;
        for (j = i - 1; j >= i - m && s[j] != s[i]; j--) ;
        sub = i - j;
        if (sub > res) res = sub;
    }

    return res;
}


int lengthOfLongestSubstringHash(string s)
{
    // longest unrepeated substring
    // solution: calculate longest unrepeated substring
    // ending with every position, use hashmap to reduce
    // time complexity

    if (s.size() <= 0)
        return 0;

    int n = s.size(), i, j;
    int res = 1, sub = 1;
    unordered_map<char, int> imap;  // last index of character
    imap[s[0]] = 0;
    for (i = 1; i < s.size(); i++)
    {
        if (imap.find(s[i]) == imap.end() || i - imap[s[i]] > sub)
            sub += 1;
        else
            sub = i - imap[s[i]];
        
        if (sub > res) res = sub;
        imap[s[i]] = i;
    }

    return res;
}


int lengthOfLongestSubstring(string s)
{
    // longest unrepeated substring
    // solution: calculate longest unrepeated substring
    // ending with every position, use hashmap to reduce
    // time complexity

    if (s.size() <= 0)
        return 0;

    int i, res = 1, sub = 1;  // length of longest unrepeated substring
    int imap[128] = {0};  // last index of character
    imap[s[0]] = 1;
    for (i = 1; i < s.size(); i++)
    {
        sub = (i + 1) - max(imap[s[i]], i - sub);
        res = max(res, sub);
        imap[s[i]] = i + 1;
    }

    return res;
}


int main(int argc, char *argv[])
{
    string s(argv[1]);
    int res;

    cout << s << endl;

    res = lengthOfLongestSubstring(s);
    cout << res << endl;

    return 0;
}