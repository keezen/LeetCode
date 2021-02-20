/*
138. Copy List with Random Pointer
Medium

A linked list of length n is given such that each node contains an additional
random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly
n brand new nodes, where each new node has its value set to the value of
its corresponding original node. Both the next and random pointer of the
new nodes should point to new nodes in the copied list such that the pointers
in the original list and copied list represent the same list state. None of
the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list,
where X.random --> Y, then for the corresponding two nodes x and y
in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes.
Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random
    pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.


Example 1:
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Example 4:
Input: head = []
Output: []
Explanation: The given linked list is empty (null pointer), so return null.
 

Constraints:

0 <= n <= 1000
-10000 <= Node.val <= 10000
Node.random is null or is pointing to some node in the linked list.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <unordered_map>
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


struct Node {
    int val;
    Node *next;
    Node *random;
    Node(int x): val(x), next(NULL), random(NULL) {}
};


void PrintList(Node * head)
{
    // print out a linked list
    Node *p = NULL;
    for (p = head; p != NULL; p = p->next)
    {
        cout << p->val << ' ';
    }
    cout << endl;
}


Node* copyRandomListHash(Node* head)
{
    // deep copy of random linked list
    // solution: construct list, then connect random link with HashMap

    if (head == NULL)
        return head;
    
    // create nodes
    unordered_map<Node*, Node*> umap;
    Node *res = new Node(0), *tail = res, *node, *p;
    for (node = head; node != NULL; node = node->next)
    {
        p = new Node(node->val);
        tail->next = p;
        tail = p;
        umap[node] = p;
    }

    p = res;
    res = res->next;
    delete p;

    // link random
    for (p = res, node = head; p != NULL && node != NULL; p = p->next, node = node->next)
        if (node->random != NULL)
            p->random = umap[node->random];
        else
            p->random = NULL;

    return res;
}


Node* copyRandomList(Node* head)
{
    // deep copy of random linked list
    // solution: insert each copied node after original, copy random link, 
    //    split new list

    if (head == NULL)
        return head;
    
    // insert copied node
    Node *res, *p, *q;
    for (p = head; p != NULL; p = p->next->next)
    {
        q = new Node(p->val);
        q->next = p->next;
        p->next = q;
    }

    // copy random link
    for (p = head; p != NULL; p = p->next->next)
    {
        q = p->next;
        if (p->random == NULL)
            q->random = NULL;
        else
            q->random = p->random->next;
    }

    // split new list
    Node *tail;
    tail = res = new Node(0);
    for (p = head; p != NULL; p = p->next)
    {
        q = p->next;
        tail->next = q;
        tail = q;
        p->next = q->next;
    }

    q = res;
    res = res->next;
    delete q;

    return res;
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    Node *res;

    string line;
    while(getline(myfile, line))
    {
        Node *head = new Node(0), *tail = head, *node;
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            node = new Node(x);
            tail->next = node;
            tail = node;
        }
        node = head;
        head = head->next;
        delete node;

        PrintList(head);

        res = copyRandomList(head);
        PrintList(res);
    }

    myfile.close();
    return 0;
}