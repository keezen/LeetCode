/*
121. Best Time to Buy and Sell Stock
Easy

Say you have an array for which the ith element is the price of
a given stock on day i.

If you were only permitted to complete at most one transaction
(i.e., buy one and sell one share of the stock), design an
algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
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


int maxProfit(vector<int>& prices)
{
    // maximum profit of array
    // solution: dynamic programming, maximum on the right of every position

    if (prices.size() <= 0)
        return 0;

    int n = prices.size(), i;
    int max_right = prices[n - 1];
    int res = 0;

    for(i = n - 2; i >= 0; i--)
    {
        max_right = max(max_right, prices[i+1]);
        res = max(max_right - prices[i], res);
    }

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    int res;

    string line;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x;

        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        res = maxProfit(data);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}
