/*
10. Regular Expression Matching
Hard

Given an input string (s) and a pattern (p), implement regular
expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z,
and characters like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element,
'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time.
Therefore, it matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
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


bool isMatch(string s, string p)
{
    // whether string s and pattern p match
    // solution: dynamic programming,
    // dp(i,j) indicates whther s[:i] matches p[:j]
    // dp(i,j) = dp[i-1][j-1] and (s[i] = p[j] or p[j] = '.'), if p[j] != '*'
    // dp(i,j) = dp[i][j-2] or ( dp[i-1][j] and (p[j-1] = s[i] or p[j-1] = '.') ), if p[j] = '*'

    int n = s.size(), m = p.size();
    vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
    int i, j;

    for (i = 0; i <= n; i++)
        dp[i][0] = false;
    dp[0][0] = true;
    
    for (j = 1; j <= m; j++)
        for (i = 0; i <= n; i++)
            if (p[j-1] != '*')
            {
                if (i > 0 && (s[i-1] == p[j-1] || p[j-1] == '.'))
                    dp[i][j] = dp[i-1][j-1];
            }
            else if (j >= 2)
            {
                if (i == 0)
                    dp[i][j] = dp[i][j-2];
                else
                    dp[i][j] = dp[i][j-2] ||
                        ( dp[i-1][j] && (p[j-2] == s[i-1] || p[j-2] == '.') );
            }
            
    return dp[n][m];
}


bool isMatch(string s, string p, int i, int j)
{
    // whether s[i:] and p[j:] matches

    if (j >= p.size())
        return i >= s.size();

    if (p[j] == '*')
        return false;

    int n = s.size(), m = p.size();
    if (j == m - 1)
        return i == n - 1 && (s[i] == p[j] || p[j] == '.');

    if (p[j+1] != '*')
    {
        if (i >= n)
            return false;

        if (s[i] == p[j] || p[j] == '.')
            return isMatch(s, p, i + 1, j + 1);
    }
    else  // p[j+1] == '*'
    {
        int res = false;
        if (i < n && (s[i] == p[j] || p[j] == '.'))
            res = isMatch(s, p, i + 1, j) || res;
        res = res || isMatch(s, p, i, j + 2);

        return res;
    }

    return false;
}


bool isMatchRecur(string s, string p)
{
    // whether string s and pattern p match
    // solution: recursive call,

    return isMatch(s, p, 0, 0);
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string s, p;
    bool res;

    while(getline(myfile, s))
    {
        getline(myfile, p);
        cout << s << endl << p << endl;
        res = isMatch(s, p);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}