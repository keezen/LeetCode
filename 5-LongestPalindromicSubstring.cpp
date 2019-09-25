/*
5. Longest Palindromic Substring
Medium

Given a string s, find the longest palindromic substring in s.
You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
using namespace std;


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


string longestPalindromeDP(string s)
{
    // longest palindromic substring
    // solution: dynamic programming
    // dp(i,j) indicates whether substring s_{i:j} is a palindrome
    // dp(i,j) = dp(i+1,j-1) and s[i] == s[j]

    if (s.size() <= 0)
        return s;
    
    int n = s.size();
    vector<vector<bool> > dp(n, vector<bool>(n, false));
    int i, j;
    int imax = 0, jmax = 0;

    for (i = 0; i < n; i++)
        dp[i][i] = true;
    for (i = 0; i < n - 1; i++)
        if (s[i] == s[i + 1])
        {
            dp[i][i + 1] = true;
            if (jmax - imax < 1)
            {
                imax = i; jmax = i + 1;
            }
        }

    for (j = 2; j < n; j++)
        for (i = j - 2; i >= 0; i--)
        {
            dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j];
            if (dp[i][j] && (j - i) > (jmax - imax))
            {
                imax = i; jmax = j;
            }
        }

    return s.substr(imax, jmax - imax + 1);
}


string longestPalindromeCenter(string s)
{
    // longest palindromic substring
    // solution: check every position as center

    if (s.size() <= 0)
        return s;
    
    int n = s.size();
    int i, j, low;
    int start = 0, width = 1;

    for (i = 0; i < n; i++)
    {
        low = max(2 * i - n + 1, 0);
        for (j = i - 1; j >= low; j--)
            if (s[j] != s[2 * i - j])
                break;

        if (2 * (i - j) - 1 > width)
        {
            start = j + 1; width = 2 * (i - j) - 1;
        }

        low = max(2 * i - n + 2, 0);
        for (j = i; j >= low; j--)
            if (s[j] != s[2 * i + 1 - j])
                break;

        if (2 * (i - j) > width)
        {
            start = j + 1; width = 2 * (i - j);
        }
    }

    return s.substr(start, width);
}


int expandAroundCenter(string s, int left, int right)
{
    // expand substring

    if (left > right)
        return 0;

    int l = left, r = right;
    for (; l >= 0 && r < s.size() && s[l] == s[r]; l--, r++) ;
    return (r - l - 1);
}


string longestPalindrome(string s)
{
    // longest palindromic substring
    // solution: check every position as center

    if (s.size() <= 0)
        return s;
    
    int n = s.size(), i;
    int start = 0, end = 0;

    for (i = 0; i < n; i++)
    {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = max(len1, len2);

        if (len > end - start + 1)
        {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    return s.substr(start, end - start + 1);
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string s;
    string res;

    getline(myfile, s);
    cout << s << endl;

    res = longestPalindrome(s);
    cout << res << endl;

    myfile.close();
    return 0;
}