/*
79. Word Search
Medium

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell,
where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once.

Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
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


bool dfs(int x, int y, vector<vector<char> > &board, int pos, string &word, vector<vector<bool> > &visited)
{
    if (pos >= word.size())
        return true;

    int m = board.size(), n = board[0].size();
    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y])
        return false;

    if (board[x][y] != word[pos])
        return false;

    if (pos == word.size() - 1)
        return true;

    visited[x][y] = true;

    // top
    if (dfs(x-1, y, board, pos+1, word, visited))
        return true;

    // bottom
    if(dfs(x+1, y, board, pos+1, word, visited))
        return true;

    // left
    if (dfs(x, y-1, board, pos+1, word, visited))
        return true;

    // right
    if(dfs(x, y+1, board, pos+1, word, visited))
        return true;

    visited[x][y] = false;

    return false;
}


bool exist(vector<vector<char> >& board, string word)
{
    // whether word can be represented by board path
    // solution: DFS
    if (word.size() <= 0 || board.size() <= 0 || board[0].size() <= 0)
        return false;

    int m = board.size(), n = board[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    int i, j;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (dfs(i, j, board, 0, word, visited))
                return true;

    return false;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    bool res;

    string arr[3] = {"ABCE", "SFCS", "ADEE"};
    vector<vector<char> > board(3, vector<char>(4));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = arr[i][j];

    for (int i = 0; i < board.size(); i++)
        PrintVec(board[i]);

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        string word;
        ss >> word;

        cout << word << endl;

        res = exist(board, word);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}
