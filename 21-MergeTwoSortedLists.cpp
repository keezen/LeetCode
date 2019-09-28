/*
21. Merge Two Sorted Lists
Easy

Merge two sorted linked lists and return it as a new list.
The new list should be made by splicing together the nodes
of the first two lists.

Example:
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
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


ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    // merge two sorted list
    // solution: pick smaller node from two list heads

    ListNode *head, *tail, *node;
    ListNode **p;

    head = tail = new ListNode(0);  // redundant node
    while (l1 != NULL && l2 != NULL)
    {
        p = (l1->val < l2->val) ? &l1 : &l2;
        tail->next = (*p); tail = (*p);
        (*p) = (*p)->next; tail->next = NULL;
    }

    node = (l1 == NULL) ? l2 : l1;
    tail->next = node;
    node = head; head = head->next; delete node;

    return head;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    ListNode *res;

    string line;
    while(getline(myfile, line))
    {
        ListNode *l1, *l2;
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
        l1 = head;

        getline(myfile, line);
        stringstream ss2(line);
        tail = head = node;
        while (ss2 >> x)
        {
            node = new ListNode(x);
            tail->next = node;
            tail = node;
        }
        node = head; head = head->next; delete node;
        l2 = head;

        PrintList(l1);
        PrintList(l2);

        res = mergeTwoLists(l1, l2);
        PrintList(res);
    }

    myfile.close();
    return 0;
}