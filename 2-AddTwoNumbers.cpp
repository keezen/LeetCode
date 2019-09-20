/*
2. Add Two Numbers
Medium

You are given two non-empty linked lists representing two non-negative
integers. The digits are stored in reverse order and each of their 
nodes contain a single digit. Add the two numbers and return it as
a linked list.

You may assume the two numbers do not contain any leading zero, except
the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/

# include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


void PrintList(ListNode *l)
{
    ListNode *p;
    for (p = l; p != NULL; p = p->next)
        cout << p->val << " ";
    cout << endl;
}


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    // add two number in the form of reverse linked list
    // solution: elementary addition, carry

    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    ListNode *p, *q, *t, *head = NULL, *tail = NULL;
    int carry = 0, cur;

    for (p = l1, q = l2; p != NULL && q != NULL; p = p->next, q = q->next)
    {
        cur = p->val + q->val + carry;
        carry = cur / 10;
        cur = cur % 10;

        t = new ListNode(cur);
        if (tail == NULL)
            head = tail = t;
        else
        {
            tail->next = t;
            tail = t;
        }
    }

    if (p == NULL)
        p = q;
    for (; p != NULL; p = p->next)
    {
        cur = p->val + carry;
        carry = cur / 10;
        cur = cur % 10;

        t = new ListNode(cur);
        tail->next = t;
        tail = t;
    }

    if (carry > 0)
    {
        t = new ListNode(carry);
        tail->next = t;
        tail = t;
    }

    return head;
}


int main(int argc, char *argv[])
{
    string line;
    ListNode *l1, *l2, *res, *t;

    l1 = new ListNode(2);
    t = new ListNode(4);
    l1->next = t;
    t = new ListNode(3);
    l1->next->next = t;

    l2 = new ListNode(5);
    t = new ListNode(6);
    l2->next = t;
    t = new ListNode(4);
    l2->next->next = t;

    PrintList(l1);
    PrintList(l2);

    res = addTwoNumbers(l1, l2);
    PrintList(res);

    return 0;
}