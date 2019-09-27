/*
20. Valid Parentheses
Easy

Given a string containing just the characters '(', ')',
'{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:
Input: "()"
Output: true

Example 2:
Input: "()[]{}"
Output: true

Example 3:
Input: "(]"
Output: false

Example 4:
Input: "([)]"
Output: false

Example 5:
Input: "{[]}"
Output: true
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


bool isValid(string s)
{
    // whether a string consisting of parenthesis is valid
    // solution: stack to keep most recent parenthesis

    if (s.size() <= 0)
        return true;

    string st;
    char c;
    for (int i = 0; i < s.size(); i++)
    {
        c = s[i];
        if (c == '(' || c == '[' || c == '{')
            st.push_back(c);
        else if (c == ')')
        {
            if (st.empty() || st.back() != '(')  // mis-matched
                return false;
            else
                st.pop_back();            
        }
        else if (c == ']')
        {
            if (st.empty() || st.back() != '[')
                return false;
            else
                st.pop_back();            
        }
        else if (c == '}')
        {
            if (st.empty() || st.back() != '{')
                return false;
            else
                st.pop_back();            
        }
    }

    if (st.empty())  // all closed
        return true;

    return false;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    bool res;

    string s;
    while(getline(myfile, s))
    {
        cout << s << endl;

        res = isValid(s);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}