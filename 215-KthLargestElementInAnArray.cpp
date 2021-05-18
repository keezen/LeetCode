/*
215. Kth Largest Element in an Array
Medium

Given an integer array nums and an integer k, return the kth largest
element in the array.

Note that it is the kth largest element in the sorted order, not the
kth distinct element.

 
Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <unordered_set>
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


int partition(int start, int end, vector<int> &nums)
{
    // find partition pivot of array
    if (start > end || nums.size() <= 0 || start < 0 || end >= nums.size())
        return -1;

    int i = start, j = end - 1, t, last = nums[end];
    while (i <= j)
    {
        if (nums[i] >= last)
            i++;
        else
        {
            swap(nums[i], nums[j]);
            j--;
        } 
    }

    swap(nums[i], nums[end]);
    return i;
}


int findKthLargestPartition(vector<int>& nums, int k)
{
    // find k-th largest element in array
    // solution: partition, narrow down recursively

    if (nums.size() <= 0 || nums.size() < k || k <= 0)
        return -1;

    int start = 0, end = nums.size() - 1, pivot;
    while (start <= end)
    {
        pivot = partition(start, end, nums);
        if (pivot == k - 1)
            return nums[pivot];
        
        if (pivot > k - 1)
            end = pivot - 1;
        else
            start = pivot + 1;
    }

    return nums[0];
}


int findKthLargest(vector<int>& nums, int k)
{
    // find k-th largest element in array
    // solution: minimum heap, if heap top less than current element,
    //     replace heap top with current

    if (nums.size() <= 0 || nums.size() < k || k <= 0)
        return -1;

    vector<int> largest;
    int i, j, p;
    for (i = 0; i < nums.size(); i++)
    {
        if (largest.size() < k)
        {
            largest.push_back(nums[i]);
            
            // heapify bottom up
            j = largest.size() - 1;
            while (j > 0)
            {
                p = (j+1)/2-1;
                if (largest[j] >= largest[p])
                    break;
                swap(largest[j], largest[p]);
                j = p;
            }
        }
        else if (largest[0] < nums[i])
        {
            largest[0] = nums[i];

            // heapify top down
            j = 0;
            while (j <= k/2-1)
            {
                p = 2*(j+1)-1;
                if (p + 1 < k && largest[p+1] < largest[p])
                    p++;
                if (largest[j] <= largest[p])
                    break;
                swap(largest[j], largest[p]);
                j = p;
            }
        }
    
        // PrintVec(largest);
    }

    return largest[0];
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

        int k = 4;
        res = findKthLargest(nums, k);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}