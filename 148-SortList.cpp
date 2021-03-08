/*
148. Sort List
Medium


Given the head of a linked list, return the list after sorting
it in ascending order.

Follow up: Can you sort the linked list in O(n logn) time and
O(1) memory (i.e. constant space)?

 
Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:
Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-105 <= Node.val <= 105
Accepted
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


ListNode* sortList(ListNode* head)
{
    // sort linked list
    // solution: merge sort  
    if (head == NULL || head->next == NULL)
        return head;

    // find half
    ListNode *s, *f;
    s = head;
    f = head->next;
    while (f != NULL && f->next != NULL)
    {
        s = s->next;
        f = f->next->next;
    }

    // sort sub-list
    f = s->next;
    s->next = NULL;
    s = sortList(head);
    f = sortList(f);

    // merge two sorted sub-list
    head = new ListNode(0);
    ListNode *tail = head;
    while (s != NULL && f != NULL)
    {
        // take smaller
        if (s->val <= f->val)
        {
            tail->next = s;
            s = s->next;
        }
        else
        {
            tail->next = f;
            f = f->next;
        }
        tail = tail->next;
        tail->next = NULL;
    }

    if (s != NULL)
        tail->next = s;
    else
        tail->next = f; 

    s = head;
    head = head->next;
    delete s;   

    return head;  
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

        res = sortList(head);
        PrintList(res);
    }

    myfile.close();
    return 0;
}