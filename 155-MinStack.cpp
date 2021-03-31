/*
155. Min Stack
Easy

Design a stack that supports push, pop, top, and retrieving the
minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 

Example 1:
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:
Methods pop, top and getMin operations will always be called on non-empty stacks.
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


struct ListNode {
    int key;
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode(int k, int v): key(k), val(v), next(NULL), prev(NULL) {}
};


void PrintList(ListNode * head)
{
    // print out a linked list
    ListNode *p = NULL;
    for (p = head; p != NULL; p = p->next)
    {
        cout << p->val << ' ';
    }
    cout << endl;
}


class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        st.clear();
        mst.clear();
    }

    void push(int x) {
        st.push_back(x);
        if (mst.size() > 0)
            mst.push_back(min(mst.back(), x));
        else
            mst.push_back(x);    
    }

    void pop() {
        st.pop_back();
        mst.pop_back();
    }

    int top() {
        return st.back();
    }

    int getMin() {
        return mst.back();
    }
private:
    vector<int> st;
    vector<int> mst;
};


int main(int argc, char *argv[])
{
    // fstream myfile("a.txt");

    int res;

    // string line;
    // while(getline(myfile, line))
    // {
    //     stringstream ss(line);
    //     int x;
    //     vector<int> nums;
    //     while (ss >> x)
    //         nums.push_back(x);

    //     PrintVec(nums);

    //     res = singleNumber(nums);
    //     cout << res << endl;
    // }

    // myfile.close();


    MinStack minStack = MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    res = minStack.getMin(); // return -3
    cout << res << endl;
    minStack.pop();
    res = minStack.top();    // return 0
    cout << res << endl;
    res = minStack.getMin(); // return -2
    cout << res << endl;

    return 0;
}