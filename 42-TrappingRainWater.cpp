/*
42. Trapping Rain Water
Hard

Given n non-negative integers representing an elevation map where
the width of each bar is 1, compute how much water it is able to
trap after raining.

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.
Thanks Marcos for contributing this image!

Example:
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
using namespace std;


template <typename T> ostream & operator<<(ostream &os, pair<T,T> &x)
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


int trapValley(vector<int>& height)
{
    // water volume to trap
    // solution: find valley, split array into range

    if (height.size() <= 2)
        return 0;

    vector<int> grad;
    int n = height.size(), i, j;

    // gradient
    for (i = 0; i < n - 1; i++)
        grad.push_back(height[i+1] - height[i]);

    // peek and valley
    vector<int> pivot;
    int last = 0;
    for (i = 0; i < n - 1 && grad[i] == 0; i++) ;
    if (i == n - 1)
        return 0;
    pivot.push_back(i);

    last = grad[i];
    for (i += 1; i < n - 1; i++)
    {
        if (grad[i] == 0)
            continue;
        
        if (grad[i] * last < 0)
        {
            pivot.push_back(i);
            last = grad[i];
        }
    }

    for (i = n - 2; i >= 0 && grad[i] == 0; i--) ;
    if (i < 0)
        return 0;
    pivot.push_back(i + 1);

    // range
    int l, r;
    vector<pair<int,int> > range;
    for (i = 1; i < pivot.size() - 1; i++)
    {
        if (grad[pivot[i]] > 0)
        {
            l = pivot[i - 1];
            r = pivot[i + 1];

            if (range.empty())
                range.push_back(make_pair(l, r));
            else
            {
                while (!range.empty())
                {
                    int tl = range.back().first;
                    int tr = range.back().second;
                    if (height[tr] == height[l] && height[tl] >= height[l] && height[r] >= height[l])
                    {
                        range.pop_back();
                        l = tl;
                    }
                    else
                        break;
                }
                range.push_back(make_pair(l, r));
            }
        }
    }

    // water to trap
    int v = 0, t;
    for (i = 0; i < range.size(); i++)
    {
        l = range[i].first;
        r = range[i].second;
        t = min(height[l], height[r]);
        for (j = l; j <= r; j++)
            if (height[j] < t)
                v += t - height[j];
    }

    return v;
}


int trapBrute(vector<int>& height)
{
    // water volume to trap
    // solution: brute force, o(n^2)
    // for every position, find max heights on both sides,
    // min of these two max heights minus its own height,
    // is max water this position can trap

    if (height.size() <= 2)
        return 0;

    int n = height.size(), i, j;
    int maxl, maxr;
    int res = 0;
    for (i = 0; i < n; i++)
    {
        // max height in left
        maxl = 0;
        for (j = 0; j <= i; j++)
            maxl = max(maxl, height[j]);

        // max height in right
        maxr = 0;
        for (j = i; j < n; j++)
            maxr = max(maxr, height[j]);

        res += min(maxl, maxr) - height[i];
    }

    return res;
}


int trapDP(vector<int>& height)
{
    // water volume to trap
    // solution: dynamic programing,
    // compute max height left and right to every position recursively
    // use min of them minus current height, is water it can trap

    if (height.size() <= 2)
        return 0;

    int n = height.size();
    vector<int> max_left(n, 0), max_right(n, 0);
    int i;

    max_left[0] = height[0];
    for (i = 1; i < n; i++)
        max_left[i] = max(max_left[i-1], height[i]);

    max_right[n-1] = height[n-1];
    for (i = n - 2; i >= 0; i--)
        max_right[i] = max(max_right[i+1], height[i]);

    int res = 0;
    for (i = 0; i < n; i++)
        res += min(max_left[i], max_right[i]) - height[i];

    return res;
}


int trapStack(vector<int>& height)
{
    // water volume to trap
    // solution: stack to save index,
    // if current height is smaller than top height, push into stack;
    // if current height is larger than top height, pop from stack,
    // res += dist(cur, top) * (min(cur, top) - pop)

    if (height.size() <= 2)
        return 0;

    int n = height.size();
    vector<int> st;

    int res = 0;
    int cur = 0, top, pop;
    while (cur < n)
    {
        if (st.empty() || height[cur] <= height[st.back()])
        {
            st.push_back(cur);
            cur++;
        }
        else  // current height larger than top
        {
            pop = st.back(); st.pop_back();
            if (st.empty())
            {
                st.push_back(cur);
                cur++;
            }
            else
            {
                top = st.back();
                res += (cur - top - 1) * ( min(height[top], height[cur]) - height[pop] );
            }
        }
    }

    return res;
}


int trap(vector<int>& height)
{
    // water volume to trap
    // solution: two pointers
    // if height[left] < height[right], res += left_max - height[left];
    // else, res += right_max - height[right]

    if (height.size() <= 2)
        return 0;

    int n = height.size();
    int res = 0;
    int left = 0, right = n - 1, max_left = 0, max_right = 0;

    while (left <= right)
    {
        if (height[left] < height[right])
        {
            max_left = max(height[left], max_left);
            res += max_left - height[left];
            left++;
        }
        else
        {
            max_right = max(height[right], max_right);
            res += max_right - height[right];
            right--;
        }
        
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
        int x;
        vector<int> nums;
        while (ss >> x)
            nums.push_back(x);

        PrintVec(nums);

        res = trap(nums);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}