/*
208. Implement Trie (Prefix Tree)
Medium

A trie (pronounced as "try") or prefix tree is a tree data structure used
to efficiently store and retrieve keys in a dataset of strings. 
There are various applications of this data structure, such as 
autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie
(i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously
inserted string word that has the prefix prefix, and false otherwise.
 

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
 

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, search, and startsWith.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
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
    char val;
    ListNode *next;
    ListNode *child;
    ListNode(char c): val(c), next(NULL), child(NULL) {}
};


class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new ListNode('\0');
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        // uset.insert(word);
        int i;
        ListNode *cur, *prev = root, *last, *p;
        for (i = 0; i <= word.size(); i++)
        {
            // search current character
            char c = word[i];
            last = NULL;
            for (p = prev->child; p != NULL; last=p, p=p->next)
                if (p->val == c)
                    break;

            // already existed
            if (p != NULL)
                prev = p;
            else  // not existed, add to child
            {
                cur = new ListNode(c);
                if (last == NULL)
                    prev->child = cur;
                else
                    last->next = cur;
                prev = cur;
            }
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        int i;
        ListNode *prev = root, *p;
        for (i = 0; i <= word.size(); i++)
        {
            char c = word[i];
            for (p = prev->child; p != NULL; p = p->next)
                if (p->val == c)
                    break;

            if (p == NULL)
                return false;
            else
                prev = p;
        }

        return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int i;
        ListNode *prev = root, *p;
        for (i = 0; i < prefix.size(); i++)
        {
            char c = prefix[i];
            for (p = prev->child; p != NULL; p = p->next)
                if (p->val == c)
                    break;

            if (p == NULL)
                return false;
            else
                prev = p;
        }
        return true;
    }

private:
    // unordered_set<string> uset;
    ListNode *root;
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


int main(int argc, char *argv[])
{
    // fstream myfile("a.txt");

    bool res;

    Trie *trie = new Trie();
    trie->insert("apple");
    res = trie->search("apple");   // return True
    cout << res << endl;
    res = trie->search("app");     // return False
    cout << res << endl;
    res = trie->startsWith("app"); // return True
    cout << res << endl;
    trie->insert("app");
    res = trie->search("app");     // return True
    cout << res << endl;

    return 0;
}