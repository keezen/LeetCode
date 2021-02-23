/*
142. Linked List Cycle II
Medium

Given a linked list, return the node where the cycle begins.
If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the
list that can be reached again by continuously following the next pointer.
Internally, pos is used to denote the index of the node that tail's next
pointer is connected to. Note that pos is not passed as a parameter.

Notice that you should not modify the linked list.

 
Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
 

Constraints:
The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
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


ListNode *detectCycle(ListNode *head)
{
    // find node where the cycle begins
    // solution: fast-slow pointers find cycle, two slow pointers find
    //     beginning

    if (head == NULL)
        return head;

    // find cycle, fast and slow
    ListNode *s, *f;
    s = head;
    f = head->next;
    while (s != NULL && f != NULL && s != f)
    {
        s = s->next;
        f = f->next;
        if (f != NULL)
            f = f->next;
    }

    // no cycle
    if (s == NULL || f == NULL)
        return NULL;

    // find beginning, two slow
    f = head;
    s = s->next;
    while (f != s)
    {
        f = f->next;
        s = s->next;
    }

    return f;
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

        tail->next = head->next;
        // PrintList(head);

        res = detectCycle(head);
        cout << res->val << endl;
    }

    myfile.close();
    return 0;
}