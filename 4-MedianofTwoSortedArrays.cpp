/*
4. Median of Two Sorted Arrays
Hard

There are two sorted arrays nums1 and nums2 of size m and n
respectively.

Find the median of the two sorted arrays. The overall run
time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_map>
# include <climits>
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


int BinarySearch(int val, vector<int>& nums, int l, int r)
{
    // binary search value in given sorted array, return index
    if (nums.size() <= 0 || l > r)
        return l - 1;

    int m;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] == val)
            return m;
        else if (nums[m] < val)
            l = m + 1;
        else
            r = m - 1;
    }

    return r;
}


int KthSmallest(int k, vector<int>& nums1, vector<int>& nums2)
{
    // k-th smallest element in two sorted arrays

    if (k <= 0 || k > nums1.size() + nums2.size())
        return -1;

    int l1 = 0, r1 = nums1.size() - 1, l2 = 0, r2 = nums2.size() - 1;
    int pos1, pos2, val, target = k, cur;
    while (l1 <= r1 && l2 <= r2)
    {
        if (r2 - l2 >= r1 - l1)
        {
            pos2 = (l2 + r2) / 2;
            val = nums2[pos2];
            pos1 = BinarySearch(val, nums1, l1, r1);
            cur = pos2 - l2 + 1 + pos1 - l1 + 1;
            if (cur == target)
                return val;
            else if (cur > target)
            {
                r1 = pos1;
                r2 = pos2 - 1;
            }
            else
            {
                l1 = pos1 + 1;
                l2 = pos2 + 1;
                target -= cur;
            }       
        }
        else
        {
            pos1 = (l1 + r1) / 2;
            val = nums1[pos1];
            pos2 = BinarySearch(val, nums2, l2, r2);
            cur = pos2 - l2 + 1 + pos1 - l1 + 1;
            if (cur == target)
                return val;
            else if (cur > target)
            {
                r1 = pos1 - 1;
                r2 = pos2;
            }
            else
            {
                l1 = pos1 + 1;
                l2 = pos2 + 1;
                target -= cur;
            }  
        }
    }

    if (l1 <= r1 && target <= r1 - l1 + 1)
        return nums1[l1 + target - 1];
    else if (l2 <= r2 && target <= r2 - l2 + 1)
        return nums2[l2 + target - 1];
    else
        return -1;
}


double findMedianSortedArraysKthSmallest(vector<int>& nums1, vector<int>& nums2)
{
    // median of two sorted arrays
    // solution: k-th smallest

    if (nums1.size() <= 0 && nums2.size() <= 0)
        return 0.0;

    int n = nums1.size() + nums2.size();
    int t1, t2;
    double res;
    if (n & 1)
        return (double) KthSmallest(n / 2 + 1, nums1, nums2);
    else
    {
        t1 = KthSmallest(n / 2, nums1, nums2);
        t2 = KthSmallest(n / 2 + 1, nums1, nums2);
        return (double) (t1 + t2) / 2.0;
    }
}


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    // median of two sorted arrays
    // solution: binary search, bi-section

    if (nums1.size() <= 0 && nums2.size() <= 0)
        return 0.0;

    int m = nums1.size(), n = nums2.size(), half = (m + n + 1) / 2;
    int l = max(0, half - n), r = min(m, half);
    int i, j;
    while (l <= r)
    {
        i = (l + r) / 2;
        j = half - i;

        // find bi-section position
        if ( (i == 0 || j == n || nums1[i-1] <= nums2[j]) &&
             (j == 0 || i == m || nums2[j-1] <= nums1[i]) )
        {
            int vl = INT_MIN, vr = INT_MAX;
            if ((m + n) & 1)  // odd items
            {
                if (i > 0) vl = max(vl, nums1[i-1]);
                if (j > 0) vl = max(vl, nums2[j-1]);
                return (double) vl;
            }
            else  // even items
            {
                if (i > 0) vl = max(vl, nums1[i-1]);
                if (j > 0) vl = max(vl, nums2[j-1]);
                if (i < m) vr = min(vr, nums1[i]);
                if (j < n) vr = min(vr, nums2[j]);
                return (double) (vl + vr) / 2.0;
            }   
        }
        else if ( (i > 0 && j < n && nums1[i-1] > nums2[j]) )
            r = i - 1;
        else
            l = i + 1;
    }
    
    return 0.0;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    vector<int> nums1, nums2;
    double res;

    string line;
    getline(myfile, line);
    stringstream ss(line);
    int x;
    while (ss >> x)
        nums1.push_back(x);

    getline(myfile, line);
    stringstream ss1(line);
    while (ss1 >> x)
        nums2.push_back(x);

    PrintVec(nums1);
    PrintVec(nums2);

    res = findMedianSortedArrays(nums1, nums2);
    cout << res << endl;

    myfile.close();
    return 0;
}