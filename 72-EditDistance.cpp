/*
72. Edit Distance
Hard

Given two words word1 and word2, find the minimum number of
operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i].first << ' ' << data[i].second << ' ';
    cout << data.back().first << ' ' << data.back().second << endl;
}


int minDistance_2dDP(string word1, string word2)
{
    int len1 = word1.size(), len2 = word2.size();
    vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1));
    int i, j;

    for (i = 0; i <= len1; i++)
        dp[i][0] = i;
    for (j = 0; j <= len2; j++)
        dp[0][j] = j;

    for (i = 1; i <= len1; i++)
        for (j = 1; j <= len2; j++)
            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(min(dp[i-1][j-1], dp[i][j-1]), dp[i-1][j]);

    return dp[len1][len2];
}


int minDistance(string word1, string word2)
{
    int len1 = word1.size(), len2 = word2.size();
    vector<int> dp(len2 + 1);
    int i, j, t, pre;

    for (j = 0; j <= len2; j++)
        dp[j] = j;

    for (i = 1; i <= len1; i++)
    {
        pre = dp[0];  // dp[i-1][j-1]
        dp[0] = i;
        for (j = 1; j <= len2; j++)
        {
            t = dp[j];
            if (word1[i - 1] == word2[j - 1])
                dp[j] = pre;
            else
                dp[j] = 1 + min(min(pre, dp[j-1]), dp[j]);
            pre = t;
        }
    }

    return dp[len2];
}


int main(int argc, char *argv[])
{
    string word1("intention");
    string word2("execution");
    int res;

    cout << word1 << endl;
    cout << word2 << endl;

    res = minDistance(word1, word2);
    cout << res << endl;

    return 0;
}