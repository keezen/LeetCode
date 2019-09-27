/*
19. Remove Nth Node From End of List
Medium

Given a linked list, remove the n-th node from the end of
list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked
list becomes 1->2->3->5.

Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
using namespace std;


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
    ListNode *p = NULL;
    for (p = head; p != NULL; p = p->next)
    {
        cout << p->val << ' ';
    }
    cout << endl;
}


ListNode* removeNthFromEnd(ListNode* head, int n)
{
    // remove n-th node from list end
    // solution: double pointer

    if (n <= 0 || head == NULL)
        return NULL;

    ListNode *p, *q;
    int i;

    // one pointer goes n steps first
    for (q = head, i = 0; i < n && q != NULL; i++)
        q = q->next;

    // n larger than length of list
    if (i < n)
        return NULL;
    
    // double pointer
    ListNode *u = new ListNode(0); u->next = head;  // redundant node
    for (p = u; p != NULL && q != NULL; p = p->next, q = q->next) ;

    ListNode *v = p->next;  // n-th node from end
    p->next = v->next;
    head = u->next;
    delete v; delete u;

    return head;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    ListNode *res;

    string line;
    while(getline(myfile, line))
    {
        ListNode *head = new ListNode(0), *tail = head, *node;
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            node = new ListNode(x);
            tail->next = node;
            tail = node;
        }
        node = head; head = head->next;
        delete node;

        getline(myfile, line);
        stringstream ss2(line);
        int n;
        ss2 >> n;

        PrintList(head);
        cout << n << endl;

        res = removeNthFromEnd(head, n);
        PrintList(head);
    }

    myfile.close();
    return 0;
}