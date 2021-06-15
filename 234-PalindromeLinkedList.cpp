/*
234. Palindrome Linked List
Easy


Given the head of a singly linked list, return true if it is a palindrome.


Example 1:
Input: head = [1,2,2,1]
Output: true

Example 2:
Input: head = [1,2]
Output: false
 

Constraints:

The number of nodes in the list is in the range [1, 105].
0 <= Node.val <= 9
 

Follow up: Could you do it in O(n) time and O(1) space?
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


bool isPalindrome(ListNode* head) 
{
    // whether a list is palindrome
    // solution: find middle, reverse second half, and compare
    if (head == NULL || head->next == NULL)
        return true;

    // find mid
    ListNode *p = head, *q = head->next, *t;
    while (p != NULL && q != NULL)
    {
        p = p->next;
        q = q->next;
        if (q != NULL)
            q = q->next;
    }

    // reverse second half
    q = NULL;
    while (p != NULL)
    {
        t = p->next;
        p->next = q;
        q = p;
        p = t;
    }

    // whether is palindrome
    p = head;
    while (p != NULL && q != NULL)
    {
        if (p->val != q->val)
            return false;
        p = p->next;
        q = q->next;
    }

    return true;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    bool res;

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

        res = isPalindrome(head);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}