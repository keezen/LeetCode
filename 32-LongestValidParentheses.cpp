/*
32. Longest Valid Parentheses
Hard

Given a string containing just the characters '(' and ')',
find the length of the longest valid (well-formed) parentheses
substring.

Example 1:
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

Example 2:
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
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


int longestValidParenthesesDP(string s)
{
    // longest valid parenthesis substring
    // solution: dynamic programming,
    // dp[i] indicates length of longest valid substring ending with position i

    if (s.size() <= 1)
        return 0;

    int n = s.size(), i;
    vector<int> dp(n, 0);
    int res = 0;

    for (i = 1; i < n; i++)
        if (s[i] == ')')
        {
            if (s[i-1] == '(')
                dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
            else if (s[i-1] == ')' && i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(')
                dp[i] = dp[i-1] + 2 + (i - dp[i-1] >= 2 ? dp[i - dp[i-1] - 2] : 0);

            res = max(dp[i], res);
        }

    return res;
}


int longestValidParenthesesStack(string s)
{
    // longest valid parenthesis substring
    // solution: stack to keep index of left parenthesis and 
    // start of current longest valid substring

    if (s.size() <= 1)
        return 0;

    int n = s.size(), i;
    vector<int> st;
    int res = 0;

    st.push_back(-1);
    for (i = 0; i < n; i++)
    {
        if (s[i] == '(')
            st.push_back(i);
        else if (s[i] == ')')
        {
            if (!st.empty())
                st.pop_back();
            if (!st.empty())
                res = max(res, i - st.back());
            if (st.empty())
                st.push_back(i);
        }
    }

    return res;
}


int longestValidParentheses(string s)
{
    // longest valid parenthesis substring
    // solution: two-pass, count number of left and right parentheses

    if (s.size() <= 1)
        return 0;

    int n = s.size(), i;
    int l, r;
    int res = 0;

    l = r = 0;
    for (i = 0; i < n; i++)
    {
        if (s[i] == '(')
            l++;
        else
            r++;
        
        if (l == r)
            res = max(res, l + r);
        else if (l < r)
        {
            l = r = 0;
        }
    }

    l = r = 0;
    for (i = n - 1; i >= 0; i--)
    {
        if (s[i] == '(')
            l++;
        else
            r++;
        
        if (l == r)
            res = max(res, l + r);
        else if (l > r)
        {
            l = r = 0;
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string s;
    while(getline(myfile, s))
    {
        cout << s << endl;

        res = longestValidParentheses(s);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}