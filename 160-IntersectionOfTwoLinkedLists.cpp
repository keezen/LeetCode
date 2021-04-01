/*
160. Intersection of Two Linked Lists
Easy

Given the heads of two singly linked-lists headA and headB, return the node at which 
the two lists intersect. If the two linked lists have no intersection at all, return null.

For example, the following two linked lists begin to intersect at node c1:

It is guaranteed that there are no cycles anywhere in the entire linked structure.

Note that the linked lists must retain their original structure after the function returns.

 

Example 1:
Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. 
There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.

Example 2:
Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. 
There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.

Example 3:
Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5].
Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.
 

Constraints:

The number of nodes of listA is in the m.
The number of nodes of listB is in the n.
0 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA <= m
0 <= skipB <= n
intersectVal is 0 if listA and listB do not intersect.
intersectVal == listA[skipA + 1] == listB[skipB + 1] if listA and listB intersect.
 

Follow up: Could you write a solution that runs in O(n) time and use only O(1) memory?
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


ListNode *getIntersectionNode3Pass(ListNode *headA, ListNode *headB)
{
    // find intersection node of two linked list
    // solution: 3 pass,
    //     1. traverse two list until end,
    //     2. traverse longer list first,
    //     3. traverse two list at same time
    if (headA == NULL || headB == NULL)
        return NULL;
    
    ListNode *p, *q, *t;
    for (p = headA, q = headB; p != NULL && q != NULL; p = p->next, q = q->next)
        ;
    
    if (q == NULL)
        t = p, q = headA, p = headB;
    else
        t = q, q = headB, p = headA;

    for (; t != NULL; t = t->next)
        q = q->next;
    
    for (; p != NULL && q != NULL; p = p->next, q = q->next)
        if (p == q)
            break;
    
    if (p == q && p != NULL)
        return p;
    else
        return NULL;
}


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    // find intersection node of two linked list
    // solution: 1 pass, if pointer is null, wrap it from another
    //     list, otherwise next node
    ListNode *p = headA, *q = headB;
    while (p != q)
    {
        p = (p == NULL ? headB : p->next);
        q = (q == NULL ? headA : q->next);
    }

    return p;   
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

        res = hasCycle(head);
        cout << res << endl;
    }

    myfile.close();
    return 0;
}