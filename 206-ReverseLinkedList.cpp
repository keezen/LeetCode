/*
206. Reverse Linked List
Easy

Given the head of a singly linked list, reverse the list, and return the 
reversed list.

 
Example 1:
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:
Input: head = [1,2]
Output: [2,1]

Example 3:
Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
 

Follow up: A linked list can be reversed either iteratively or recursively.
Could you implement both?
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
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


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
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


ListNode* reverseListR(ListNode* head)
{
    // reverse linked list
    // solution: recursion

    if (head == NULL || head->next == NULL)
        return head;

    ListNode *p = head;  // p's next will be 2nd last
    head = reverseListR(head->next);
    p->next->next = p;
    p->next = NULL;

    return head;
}


ListNode* reverseListStack(ListNode* head)
{
    // reverse linked list
    // solution: stack

    if (head == NULL)
        return head;

    vector<ListNode *> st;
    ListNode *p, *tail;
    for (p = head; p != NULL; p=p->next)
        st.push_back(p);

    head = tail = NULL;
    while (!st.empty())
    {
        p = st.back();
        st.pop_back();
        if (head == NULL)
            head = tail = p;
        else
        {
            tail->next = p;
            tail = p;
            tail->next = NULL;
        }
    }

    return head;
}


ListNode* reverseList(ListNode* head)
{
    // reverse linked list
    // solution: iterative

    if (head == NULL)
        return head;

    ListNode *p = NULL, *t;
    while (head != NULL)
    {
        t = head->next;
        head->next = p;
        p = head;
        head = t;
    }

    return p;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    ListNode *res;

    string line;
    while(getline(myfile, line))
    {
        ListNode *head = new ListNode(0), *tail = head, *p;
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            p = new ListNode(x);
            tail->next = p;
            tail = p;
        }
        p = head;
        head = head->next;
        delete p;

        PrintList(head);

        res = reverseListR(head);
        PrintList(res);
    }

    myfile.close();
    return 0;
}