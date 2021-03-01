/*
146. LRU Cache
Medium

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists.
Otherwise, add the key-value pair to the cache. If the number of keys exceeds
the capacity from this operation, evict the least recently used key.

Follow up:
Could you do get and put in O(1) time complexity?

 
Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
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
    int key;
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode(int k, int v): key(k), val(v), next(NULL), prev(NULL) {}
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


class LRUCache {
    // HashMap and double linked list
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (umap.find(key) != umap.end())
        {
            ListNode *p = umap[key];
            update(p);
            return p->val;
        }
        else
            return -1;  
    }
    
    void put(int key, int value) {
        // update node
        ListNode *p;
        if (umap.find(key) != umap.end())
            p = umap[key];
        else
        {
            p = new ListNode(key, value);
            umap[key] = p;
        }
        p->val = value;
        update(p);

        // PrintList(head);
        
        // check capacity
        if (umap.size() > cap)
        {
            // remove tail
            p = tail;
            tail = p->prev;
            if (tail != NULL)
                tail->next = NULL;
            if (p == head)
                head = NULL;
            umap.erase(p->key);
            delete p;
        }
    }

private:
    void update(ListNode *p) {
        // update node to head

        if (p == head)
            return;

        if (p == tail)
            tail = p->prev;

        if (tail == NULL)
            tail = p;

        // take out node
        if (p->prev != NULL)
            p->prev->next = p->next;
        if (p->next != NULL)
            p->next->prev = p->prev;

        // put node at head
        p->prev = NULL;
        p->next = head;
        if (head != NULL)
            head->prev = p;
        head = p;
    }

    unordered_map<int, ListNode*> umap;
    ListNode *head = NULL, *tail = NULL;
    int cap = 0;
};


int singleNumber(vector<int>& nums)
{
    // find single number
    // solution: xor operation

    if (nums.size() <= 0)
        return 0;

    int res = 0;
    for (int i = 0; i < nums.size(); i++)
        res = res ^ nums[i];
    
    return res;
}


int main(int argc, char *argv[])
{
    // fstream myfile("a.txt");

    int res;

    // string line;
    // while(getline(myfile, line))
    // {
    //     stringstream ss(line);
    //     int x;
    //     vector<int> nums;
    //     while (ss >> x)
    //         nums.push_back(x);

    //     PrintVec(nums);

    //     res = singleNumber(nums);
    //     cout << res << endl;
    // }

    // myfile.close();


    LRUCache *lRUCache = new LRUCache(2);
    lRUCache->put(1, 1); // cache is {1=1}
    lRUCache->put(2, 2); // cache is {1=1, 2=2}
    res = lRUCache->get(1);    // return 1
    cout << res << ' ' << endl;
    lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    res = lRUCache->get(2);    // returns -1 (not found)
    cout << res << ' ' << endl;
    lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    res = lRUCache->get(1);    // return -1 (not found)
    cout << res << ' ' << endl;
    res = lRUCache->get(3);    // return 3
    cout << res << ' ' << endl;
    res = lRUCache->get(4);    // return 4
    cout << res << ' ' << endl;

    return 0;
}