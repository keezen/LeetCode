/*
76. Minimum Window Substring
Hard

Given a string S and a string T, find the minimum window in S which
will contain all the characters in T in complexity O(n).

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

Note:

If there is no such window in S that covers all characters in T,
return the empty string "".
If there is such window, you are guaranteed that there will always
be only one unique minimum window in S.
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


template <typename T> ostream & operator<<(ostream &os, pair<T, T> &x)
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


string minWindow1(string s, string t)
{
    // minimum window to contain all characters in another string
    // solution: two pointers, start and end, moving start make sub-string shorter,
    // moving end to make it longer

    if (s.size() <= 0 || t.size() <= 0)
        return "";

    int cnts[128] = {0}, cntt[128] = {0};
    int i, j, start, end;
    int n = s.size();
    for (i = 0; i < s.size(); i++)
        cnts[s[i]] += 1;
    for (i = 0; i < t.size(); i++)
        cntt[t[i]] += 1;

    for (i = 0; i < 128; i++)
        if (cnts[i] < cntt[i])
            return "";

    for (j = n - 1; j > 0; j--)
        if (cntt[s[j]] > 0 && cnts[s[j]] <= cntt[s[j]])
            break;
        else
            cnts[s[j]]--;

    start = i = 0;
    end = j;
    char c;
    while (j < n)
    {
        // shorter
        for (; i <= j; cnts[s[i++]]--)
            if (cntt[s[i]] > 0 && cnts[s[i]] <= cntt[s[i]])
                break;

        if (j - i < end - start)
        {
            start = i;
            end = j;
        }

        c = s[i++];
        cnts[c]--;

        // longer
        for (j++; j < n; j++)
        {
            cnts[s[j]]++;
            if (s[j] == c)
                break;
        }
    }

    return s.substr(start, end - start + 1);
}


string minWindow(string s, string t)
{
    // minimum window to contain all characters in another string
    // solution: two pointers, start make sub-string shorter,
    // moving end to make it longer and valid

    if (s.size() <= 0 || t.size() <= 0)
        return "";

    int map[128] = {0};
    int counter;  // whether the sub-string is valid
    int i, j;  // two pointers
    int head, d = INT_MAX;  // track minimum window

    // initialize hash map
    for (i = 0; i < t.size(); i++)
        map[t[i]]++;
    counter = t.size();

    // two pointers
    i = j = 0;
    while (j < s.size())
    {
        // move end pointer make it valid
        if (map[s[j++]]-- > 0)
            counter--;

        // move start pointer make it shorter
        while (counter == 0)
        {
            if (j - i < d)
                d = j - (head = i);

            if (map[s[i++]]++ == 0)
                counter++;
        }
    }

    return d == INT_MAX ? "" : s.substr(head, d);
}



int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    string res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        string s, t;
        ss >> s >> t;

        cout << s << " " << t << endl;

        res = minWindow(s, t);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}
