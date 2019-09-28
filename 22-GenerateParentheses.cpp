/*
22. Generate Parentheses
Medium

Given n pairs of parentheses, write a function to generate
all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
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


void generateParenthesis(int l, int r, int n, string &path, vector<string> &res)
{
    if (l >= n && r >= n)
    {
        res.push_back(path);
        return;
    }

    if (l < n)
    {
        path.push_back('(');
        generateParenthesis(l + 1, r, n, path, res);
        path.pop_back();
    }

    if (l > r)
    {
        path.push_back(')');
        generateParenthesis(l, r + 1, n, path, res);
        path.pop_back();
    }
}


vector<string> generateParenthesisBacktrack(int n)
{
    // generate parentheses string given n pairs
    // solution: backtrack

    vector<string> res;
    if (n <= 0)
        return res;

    string path;
    generateParenthesis(0, 0, n, path, res);
    return res;
}


vector<string> generateParenthesis(int n)
{
    // generate parentheses string given n pairs
    // solution: enumerate closure number,
    // closure number of a valid parentheses sequence S:
    // the least c >= 0 so that S[0:2*c+1] is valid.

    vector<string> res;
    if (n <= 0)
    {
        res.push_back("");
        return res;
    }

    vector<string> left, right;
    for (int c = 0; c < n; c++)
    {
        left = generateParenthesis(c);
        right = generateParenthesis(n - c - 1);
        for (int i = 0; i < left.size(); i++)
            for (int j = 0; j < right.size(); j++)
                res.push_back("(" + left[i] + ")" + right[j]);
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string line;
    int n;
    vector<string> res;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        ss >> n;

        cout << n << endl;

        res = generateParenthesis(n);
        PrintVec(res);
    }

    myfile.close();
    return 0;
}