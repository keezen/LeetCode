/*
17. Letter Combinations of a Phone Number
Medium

Given a string containing digits from 2-9 inclusive, return
all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons)
is given below. Note that 1 does not map to any letters.

Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:

Although the above answer is in lexicographical order, your answer
could be in any order you want.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
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


void letterCombinations(int pos, string &digits, vector<string> &imap,
                        string &path, vector<string> &res)
{
    if (pos == digits.size())
    {
        res.push_back(path);
        return;
    }

    string cand = imap[digits[pos] - '2'];
    for (int i = 0; i < cand.size(); i++)
    {
        path.push_back(cand[i]);
        letterCombinations(pos + 1, digits, imap, path, res);
        path.pop_back();
    }
}


vector<string> letterCombinations(string digits)
{
    // letter combination represented by digits
    // solution: recursion, backtrack

    vector<string> res;

    if (digits.size() <= 0)
        return res;

    vector<string> imap(8, "");
    imap[0] = "abc"; imap[1] = "def"; imap[2] = "ghi";
    imap[3] = "jkl"; imap[4] = "mno"; imap[5] = "pqrs";
    imap[6] = "tuv"; imap[7] = "wxyz";

    string path = "";
    letterCombinations(0, digits, imap, path, res);
    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string s;
    vector<string> res;

    while(getline(myfile, s))
    {
        cout << s << endl;;

        res = letterCombinations(s);
        for (auto &u: res)
            cout << u << endl;
    }

    myfile.close();
    return 0;
}