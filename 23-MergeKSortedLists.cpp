/*
23. Merge k Sorted Lists
Hard

Merge k sorted linked lists and return it as one sorted list.
Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
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


bool cmp(ListNode *a, ListNode *b)
{
    if (a == NULL || b == NULL)
        return false;
    return a->val > b->val;
}


ListNode* mergeKLists(vector<ListNode*>& lists)
{
    // merge k sorted list
    // solution: use minimum heap to track list head with
    // min value

    if (lists.size() <= 0)
        return NULL;

    // initialize heap
    vector<ListNode *> heap;
    for (int i = 0; i < lists.size(); i++)
    {
        if (lists[i] != NULL)
            heap.push_back(lists[i]);
    }
    make_heap(heap.begin(), heap.end(), cmp);

    // merge list
    ListNode *head, *tail, *node;
    head = tail = new ListNode(0);
    while (!heap.empty())
    {
        // select list with min head
        pop_heap(heap.begin(), heap.end(), cmp);
        node = heap.back();
        tail->next = node; tail = node;
        node = node->next;

        // update heap
        if (node == NULL)
            heap.pop_back();
        else
        {
            heap[heap.size()-1] = node;
            push_heap(heap.begin(), heap.end(), cmp);
        }
    }

    node = head; head = head->next; delete node;

    return head;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    ListNode *res;
    vector<ListNode *> lists;
    string line;
    ListNode *head, *tail, *node = new ListNode(0);
    while(getline(myfile, line))
    {
        head = tail = node;
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            node = new ListNode(x);
            tail->next = node;
            tail = node;
        }
        node = head; head = head->next;
        lists.push_back(head);
    }
    delete node;

    for (int i = 0; i < lists.size(); i++)
        PrintList(lists[i]);

    res = mergeKLists(lists);
    PrintList(res);

    myfile.close();
    return 0;
}